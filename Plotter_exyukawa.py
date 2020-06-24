import ROOT
import sys
import os
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH2F, THStack
from ROOT import gROOT, gBenchmark, gRandom, gSystem
import ctypes
import re
import numpy
import json

#def plot_mc_data(outname,list1,list2):
def plot_mc_data(*args):
	for arg in args:
		print(arg)


pList = []
f = []

for ind, word in enumerate(sys.argv):
	if ind == 0:
		continue
	f.append(ROOT.TFile.Open(sys.argv[ind]))

#assuming all root files contain the same histograms
#use the one from MC since data has one more object by default
hist_list_data = os.popen('rootls -1 '+sys.argv[1]).read().split('\n')
hist_list_data = list(filter(None, hist_list_data))
print(hist_list_data)
hist_list_mc = os.popen('rootls -1 '+sys.argv[2]).read().split('\n')
hist_list_mc = list(filter(None, hist_list_mc))
print(hist_list_mc)
hist_list = [x for x in hist_list_data if x in hist_list_mc]
print(hist_list)
integrated_lumi = 41.5 #fb-1

os.popen('curl https://raw.githubusercontent.com/efeyazgan/TopLJets2015/106_protonreco/TopAnalysis/test/analysis/ExYukawa/samples_2017.json > samples_2017.json').read()
with open('samples_2017.json','r') as jsonfile:
	json_data = jsonfile.read()
json_obj = json.loads(json_data)
for sample in json_obj:
	print(sample, json_obj[sample][0])
print("MC13TeV_2017_TTTo2L2Nu_psweights cross section: "+str(json_obj['MC13TeV_2017_TTTo2L2Nu_psweights'][0]))

content8 = 1.
content1 = 1.
for x in hist_list:
	if "dphi_mumu_" in x:
		continue;
	if "phi1_phi2" in x:
		continue;
	histos = []
	xlabel = "title"
	ROOT.gStyle.SetOptStat(0)
	ROOT.gStyle.SetOptTitle(0)
	c=ROOT.TCanvas('c','c',500,500)
	hs = ROOT.THStack("hs","")
	hd = ROOT.THStack("hs","")
	yield_h = ROOT.TH1I()
	for ind, y in enumerate(sys.argv):
		if ind == 0:
			continue
		sample_name = sys.argv[ind]
		sample_name = re.sub('\_combined\.root','',sample_name)
		sample_name = re.sub('ntuples\/','',sample_name)
#		sample_name = re.sub('MC13TeV\_','',sample_name)
#		sample_name = re.sub('\_psweights','',sample_name)
#		sample_name = re.sub('2017\_','',sample_name)
#		sample_name = re.sub('13TeV','',sample_name)
		sample_name = re.sub('BCDEF',"B-F",sample_name)

		if "ttc" in sample_name:
			sample_name = "ttc"
		histos.append(f[ind-1].Get(x))
		histos[-1].SetTitle(sample_name)
		if "data" in sample_name.lower():
#		   histos[-1].DrawNormalized('Esame' if len(histos)>1 else 'E')
		   histos[-1].SetMarkerStyle(20)
		   histos[-1].SetMarkerColor(ind)
		   histos[-1].SetLineColor(ind)
#		   histos[-1].Draw('E')
		   xlabel = histos[-1].GetXaxis().GetTitle()
		   hd.Add(histos[-1])
		else:
#			histos[-1].DrawNormalized("HISTsame")
		   histos[-1].SetFillColor(ind)
		   histos[-1].SetLineColor(ind)
		   histos[-1].SetMarkerColor(ind)
		   if "yields" in x:
		      content8 = histos[-1].GetBinContent(8)
		      content1 = histos[-1].GetBinContent(1)
		   if "yields" not in x:
		      print(sample_name,json_obj[sample_name][0],integrated_lumi*1000.)
	              n_exp = json_obj[sample_name][0]*integrated_lumi*1000. #1000 is needed for pb/fb conversion
		      print(n_exp)
		      scale = content8*n_exp/content1
		      print("scale=",scale)
		      histos[-1].Scale(scale)
#		   histos[-1].Draw('HISTsame')
		   hs.Add(histos[-1])
	hs.Draw('HIST')
	hs.GetXaxis().SetTitle(xlabel)
	hd.Draw('Esame')
	c.BuildLegend(0.7,0.9,0.9,0.65)
	t = ROOT.TLatex()
	t.SetNDC(1)
	t.SetTextSize(0.030)
	t.DrawLatex(0.1,0.91,"CMS #it{Preliminary}")
	t.DrawLatex(0.62,0.91,"2017, 13 TeV, 41.5 fb^{-1}")
	c.Modified()
	c.Update()
	c.SaveAs(x+'.root')

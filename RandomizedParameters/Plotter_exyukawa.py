import ROOT
import sys
import os
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH2F, THStack
from ROOT import gROOT, gBenchmark, gRandom, gSystem
import ctypes
import re
import numpy

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

for x in hist_list:
	if "dphi_mumu_" in x:
		continue;
	histos = []
	ROOT.gStyle.SetOptStat(0)
	ROOT.gStyle.SetOptTitle(0)
	c=ROOT.TCanvas('c','c',500,500)
	hs = ROOT.THStack("hs","");
	for ind, y in enumerate(sys.argv):
		if ind == 0:
			continue
		sample_name = sys.argv[ind]
		sample_name = re.sub('\_combined\.root','',sample_name)
		sample_name = re.sub('ntuples\/','',sample_name)
		sample_name = re.sub('MC13TeV\_','',sample_name)
		sample_name = re.sub('\_psweights','',sample_name)
		histos.append(f[ind-1].Get(x))
		histos[-1].SetTitle(sample_name)
		if "data" in sample_name.lower():
#			histos[-1].DrawNormalized('Esame' if len(histos)>1 else 'E')
		   histos[-1].SetLineColor(ind)
		   histos[-1].Draw('E')
		else:
#			histos[-1].DrawNormalized("HISTsame")
		   histos[-1].SetFillColor(ind)
		   histos[-1].SetLineColor(ind)
		   histos[-1].SetMarkerColor(ind)
		   print("*** WARNING - 1E6 SCALE FOR MC PLOTS FOR DEBUGGING")
		   histos[-1].Scale(1E6)
#		   histos[-1].Draw('HISTsame')
		   hs.Add(histos[-1])
	hs.Draw('HISTsames')
	c.BuildLegend(0.65,0.95,0.95,0.8)
	c.Modified()
	c.Update()
	c.SaveAs(x+'.pdf')

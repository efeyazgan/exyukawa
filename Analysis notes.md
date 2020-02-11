Analysis notes

**Main program:** TopLJets2015/TopAnalysis
**Branch:** 106_protonreco

**List of triggers, filters etc. defined in:**
``
CMSSW_10_6_2/src/TopLJets2015/TopAnalysis/python/miniAnalyzer_cfi.py
CMSSW_10_6_2/src/TopLJets2015/TopAnalysis/python/customizeInputFiles.py 
`` (as the name implies)
Made some modifications in plugins/MiniAnalyzer.cc --> This is the main program that does the cuts etc. 

## Main Background samples [UL17 MiniAod or GEN if MiniAod doesn't exist]: ##

**ttbar+jets**
````
TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8	149329516 TOP-RunIISummer19UL17MiniAOD-00054	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	200000	PPD-RunIISummer19UL17MiniAOD-00002	new
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	200000	PPD-RunIISummer19UL17MiniAOD-00007	approved
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	200000	PPD-RunIISummer19UL17MiniAOD-00009	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	200000	PPD-RunIISummer19UL17MiniAOD-00010	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	10000	PPD-RunIISummer19UL17MiniAOD-00011	new
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	10000	PPD-RunIISummer19UL17MiniAOD-00013	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8_PPD	200000	PPD-RunIISummer19UL17MiniAOD-00014	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	131983300	TOP-RunIISummer19UL17MiniAOD-00055	done
TTToHadronic_TuneCP5_13TeV-powheg-pythia8	128667500	TOP-RunIISummer19UL18MiniAOD-00011	done
TTToHadronic_TuneCP5_erdON_13TeV-powheg-pythia8	26857600	TOP-RunIISummer19UL17MiniAOD-00040	done
TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8	111829399	TOP-RunIISummer19UL18MiniAOD-00001	submitted
TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8	114253000	TOP-RunIISummer19UL17MiniAOD-00010	done
TTToSemiLeptonic_TuneCP5_erdON_13TeV-powheg-pythia8	26821400	TOP-RunIISummer19UL17MiniAOD-00038	done
TTToSemiLeptonic_TuneCP5_erdON_13TeV-powheg-pythia8	26836999	TOP-RunIISummer19UL18MiniAOD-00025	submitted
TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8	70341400	TOP-RunIISummer19UL18MiniAOD-00034	done
TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8	68471200	TOP-RunIISummer19UL17MiniAOD-00011	done
TTTo2L2Nu_TuneCP5_erdON_13TeV-powheg-pythia8	5371300	TOP-RunIISummer19UL17MiniAOD-00039	done
TTTo2L2Nu_TuneCP5_erdON_13TeV-powheg-pythia8	5248000	TOP-RunIISummer19UL18MiniAOD-00032	done
TT_Mtt-700to1000 ??
TT_Mtt-1000toInf ??
````

**Single top**
````
ST_t-channel_top_4f_InclusiveDecays_TuneCP5down_13TeV-powheg-madspin-pythia8	49936000	TOP-RunIISummer19UL17MiniAOD-00023	new
ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8	76915186	TOP-RunIISummer19UL17MiniAOD-00057	new
ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8	159505669	TOP-RunIISummer19UL17MiniAOD-00058	new
ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8	6000000	TOP-RunIISummer19UL17MiniAOD-00014	new
ST_tW_antitop_5f_inclusiveDecays_TuneCP5up_13TeV-powheg-pythia8	5000000	TOP-RunIISummer19UL17MiniAOD-00012	new
ST_tW_top_5f_hdampdown_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8	2967927	TOP-RunIISummer19UL17MiniAOD-00013	new
ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-mcatnlo-pythia8	19967300	TOP-RunIISummer19UL17MiniAOD-00048	done
````

**Wt+jets**
???

## Sub-dominant backgrounds: ##
**tth**
````
?? ttHToZG_ZToLL_M125_TuneCP5_13TeV-powheg-pythia8	50000	HIG-RunIISummer19UL17MiniAOD-00085	done
?? ttHToZG_M125_TuneCP5_13TeV-powheg-pythia8	200000	HIG-RunIISummer19UL17MiniAOD-00092	done
?? ttHJetToGG_M125_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8	433266	HIG-RunIISummer19UL17MiniAOD-00168	done
ttHJetTobb_M125 ??
ttHJetToNonbb_M125 ??
````

**ttZ**
````
TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8	750000	SUS-RunIISummer19UL17MiniAOD-00001	done
````

## Minor backgrounds: ##
**Z+jets**
````
DYJetsToLL_M-10to50 ??
DYJetsToEE_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	10099860	EGM-RunIISummer19UL17MiniAOD-00023	done
DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM_mg265-pythia8	98209	HIG-RunIISummer19UL17MiniAOD-00099	new
DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	100000000	TAU-RunIISummer19UL18MiniAOD-00003	submitted
DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	105508369	TAU-RunIISummer19UL17MiniAOD-00003	done
DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX_mg265-pythia8	100020	HIG-RunIISummer19UL17MiniAOD-00101	new
DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8	204194297	HIG-RunIISummer19UL17MiniAOD-00169	done
DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8	204690120	HIG-RunIISummer19UL18MiniAOD-00001	done
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	19984	PPD-RunIISummer19UL18MiniAOD-00002	done
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	29213602	MUO-RunIISummer19UL17MiniAOD-00001	done
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	100000	PPD-RunIISummer19UL17MiniAOD-00003	new
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	100459	PPD-RunIISummer19UL17MiniAOD-00006	done
DYJetsToMuMu_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM-pythia8	1020690	MUO-RunIISummer19UL17MiniAOD-00002	done
DYJetsToMuMu_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM_pdfwgt_F-pythia8	1055458	MUO-RunIISummer19UL17MiniAOD-00045	done
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM_pdfwgt_F-pythia8	28829555	MUO-RunIISummer19UL17MiniAOD-00049	done
DYJetsToMuMu_M-50_TuneCP5_13TeV-madgraphMLM_pdfwgt_F-pythia8	28856011	MUO-RunIISummer19UL18MiniAOD-00001	done
DYJetsToMuMu_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM_pdfwgt_F-pythia8	1055371	MUO-RunIISummer19UL18MiniAOD-00002	done
DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	47627040	TAU-RunIISummer19UL17MiniAOD-00002	submitted
DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	70000000	TAU-RunIISummer19UL18MiniAOD-00004	submitted
DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	28395158	TAU-RunIISummer19UL17MiniAOD-00007	done
DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	30000000	TAU-RunIISummer19UL18MiniAOD-00005	submitted
DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	19010968	TAU-RunIISummer19UL17MiniAOD-00006	submitted
DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	20000000	TAU-RunIISummer19UL18MiniAOD-00006	submitted
DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	10000000	TAU-RunIISummer19UL18MiniAOD-00007	submitted
DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8	7588558	TAU-RunIISummer19UL17MiniAOD-00005	done
````

**W+jets**
````
WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	88139069	BTV-RunIISummer19UL17MiniAOD-00030	done
WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	80000000	BTV-RunIISummer19UL18MiniAOD-00005	new
W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	48906609	BTV-RunIISummer19UL17MiniAOD-00034	done
W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	50000000	BTV-RunIISummer19UL18MiniAOD-00001	new
W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	28947567	BTV-RunIISummer19UL17MiniAOD-00031	done
W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	30000000	BTV-RunIISummer19UL18MiniAOD-00002	new
W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	18994178	BTV-RunIISummer19UL17MiniAOD-00032	done
W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	20000000	BTV-RunIISummer19UL18MiniAOD-00003	new
W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	17420222	BTV-RunIISummer19UL17MiniAOD-00033	done
W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8	10000000	BTV-RunIISummer19UL18MiniAOD-00004	new
WjetsToLNu_HT binned samples ??
````

**4top**

````
TTTT ??
````

**3top ??**
````
TTT ??
````

**ttW**
````
TTWJetsToLNu ??
TTWJetstoQQ ??
````

**ttZ**
````
TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8	750000	SUS-RunIISummer19UL16wmLHEGEN-00001	defined
TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8	750000	SUS-RunIISummer19UL17wmLHEGEN-00001	done
TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8	750000	SUS-RunIISummer19UL18wmLHEGEN-00001	approved
TTZToLLNuNu_M-10??
````


**tWh**
??


## Other backgrouds: ##
**tZq ??**
````
tZq_ll_4f ??
````

**ttGJets ??**
````
TTGJets ??
````

**di-boson ??**
````
WWTo2L2Nu ??
WWToLNuQQ ??
WZTo1L1Nu2Q ??
WZTo1L3Nu ??
WZTo2L2Q ??
WZTo3LNu ??
ZZTo2L2Nu ??
ZZTo2L2Q ??
ZZTo4L ??
WH_HToBB_WToLNu_M125 ??
WplusH_HToZG_WToAll_ZToLL_M130_TuneCP5_13TeV-powheg-pythia8	48998	HIG-RunIISummer19UL17MiniAOD-00074	done ???
VHToNonbb_M125 ??
````

**tri-boson ??**
````
WWW_4F ??
WWZ ??
WZZ ??
ZZZ ??
````

**QCD**
````
QCD_Pt_15to30_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL17MiniAOD-00015	done
QCD_Pt_15to30_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL18MiniAOD-00009	done
QCD_Pt_30to50_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL17MiniAOD-00024	done
QCD_Pt_30to50_TuneCP5_13TeV_pythia8	20000000	MUO-RunIISummer19UL17MiniAOD-00032	done
QCD_Pt_30to50_TuneCP5_13TeV_pythia8	20000000	MUO-RunIISummer19UL18MiniAOD-00003	submitted
QCD_Pt_50to80_TuneCP5_13TeV_pythia8	20000000	MUO-RunIISummer19UL18MiniAOD-00004	done
QCD_Pt_50to80_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL17MiniAOD-00001	done
QCD_Pt_80to120_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL18MiniAOD-00005	submitted
QCD_Pt_80to120_TuneCP5_13TeV_pythia8	30000000	BTV-RunIISummer19UL17MiniAOD-00005	done
QCD_Pt_80to120_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL17MiniAOD-00028	done
QCD_Pt_120to170_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL18MiniAOD-00006	done
QCD_Pt_120to170_TuneCP5_13TeV_pythia8	30000000	BTV-RunIISummer19UL17MiniAOD-00002	done
QCD_Pt_120to170_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL17MiniAOD-00030	done
QCD_Pt_170to300_TuneCP5_13TeV_pythia8	30000000	BTV-RunIISummer19UL17MiniAOD-00007	done
QCD_Pt_170to300_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL18MiniAOD-00007	submitted
QCD_Pt_300to470_TuneCP5_13TeV_pythia8	58000000	BTV-RunIISummer19UL17MiniAOD-00003	done
QCD_Pt_300to470_TuneCP5_13TeV_pythia8	58000000	BTV-RunIISummer19UL18MiniAOD-00011	done
QCD_Pt_470to600_TuneCP5_13TeV_pythia8	27871600	BTV-RunIISummer19UL17MiniAOD-00012	done
QCD_Pt_470to600_TuneCP5_13TeV_pythia8	28000000	BTV-RunIISummer19UL18MiniAOD-00013	done
QCD_Pt_600to800_TuneCP5_13TeV_pythia8	67905500	BTV-RunIISummer19UL17MiniAOD-00017	done
QCD_Pt_600to800_TuneCP5_13TeV_pythia8	68000000	BTV-RunIISummer19UL18MiniAOD-00010	done
QCD_Pt_800to1000_TuneCP5_13TeV_pythia8	40000000	BTV-RunIISummer19UL18MiniAOD-00015	done
QCD_Pt_800to1000_TuneCP5_13TeV_pythia8	40000000	BTV-RunIISummer19UL17MiniAOD-00014	done
QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL18MiniAOD-00014	done
QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8	20000000	BTV-RunIISummer19UL17MiniAOD-00016	done
QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8	6000000	BTV-RunIISummer19UL17MiniAOD-00018	done
QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8	5904300	BTV-RunIISummer19UL18MiniAOD-00006	done
QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8	3000000	BTV-RunIISummer19UL17MiniAOD-00019	done
QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8	3000000	BTV-RunIISummer19UL18MiniAOD-00012	done
QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8	2000000	BTV-RunIISummer19UL17MiniAOD-00029	done
QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8	2000000	BTV-RunIISummer19UL18MiniAOD-00007	done
QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8	800000	BTV-RunIISummer19UL18MiniAOD-00008	done
QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8	800000	BTV-RunIISummer19UL17MiniAOD-00020	done
QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8	100000	PPD-RunIISummer19UL16MiniAOD-00001	done
QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8	100000	PPD-RunIISummer19UL16MiniAOD-00002	done
QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8	3953813	BTV-RunIISummer19UL18MiniAOD-00022	done
QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8	28562141	BTV-RunIISummer19UL17MiniAOD-00010	done
QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8	28454938	BTV-RunIISummer19UL18MiniAOD-00020	submitted
QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8	30995785	BTV-RunIISummer19UL17MiniAOD-00009	done
QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8	30951980	BTV-RunIISummer19UL18MiniAOD-00023	submitted
QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8	21037251	BTV-RunIISummer19UL18MiniAOD-00024	submitted
QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8	21087021	BTV-RunIISummer19UL17MiniAOD-00013	done
QCD_Pt_50to80_TuneCP5_13TeV_pythia8	20000000	MUO-RunIISummer19UL17MiniAOD-00029	done
QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8	613257	BTV-RunIISummer19UL17MiniAOD-00011	done
QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8	25615578	BTV-RunIISummer19UL18MiniAOD-00019	submitted
QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8	651672	BTV-RunIISummer19UL17MiniAOD-00004	done
QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8	21137132	BTV-RunIISummer19UL18MiniAOD-00021	done
QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8	36934006	BTV-RunIISummer19UL17MiniAOD-00008	done
QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8	36816743	BTV-RunIISummer19UL18MiniAOD-00025	submitted
QCD_Pt_170to300_TuneCP5_13TeV_pythia8	30000000	MUO-RunIISummer19UL17MiniAOD-00031	done
QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8	49350541	BTV-RunIISummer19UL18MiniAOD-00026	done
QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8	494796	BTV-RunIISummer19UL17MiniAOD-00025	done
QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8	517382	BTV-RunIISummer19UL17MiniAOD-00026	done
QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8	20736066	BTV-RunIISummer19UL18MiniAOD-00018	submitted
QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8	17384542	BTV-RunIISummer19UL17MiniAOD-00027	done
QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8	17412956	BTV-RunIISummer19UL18MiniAOD-00017	done
QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8	17243002	BTV-RunIISummer19UL17MiniAOD-00006	done
QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8	17194782	BTV-RunIISummer19UL18MiniAOD-00027	submitted
QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8	14937802	BTV-RunIISummer19UL17MiniAOD-00028	done
QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8	14939923	BTV-RunIISummer19UL18MiniAOD-00016	done
QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8	14390839	EGM-RunIISummer19UL17MiniAOD-00021	done
QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8	10903280	EGM-RunIISummer19UL17MiniAOD-00024	done
QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8	9536384	EGM-RunIISummer19UL17MiniAOD-00025	done
QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8	9902242	EGM-RunIISummer19UL17MiniAOD-00026	done
QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8	3728180	EGM-RunIISummer19UL17MiniAOD-00027	done
QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8	2866868	EGM-RunIISummer19UL17MiniAOD-00028	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	100	PPD-RunIISummer19UL18MiniAOD-00003	new
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL17MiniAOD-00003	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL17MiniAOD-00004	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL17MiniAOD-00005	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL17MiniAOD-00007	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	19888800	JME-RunIISummer19UL17MiniAOD-00009	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	19888800	JME-RunIISummer19UL17MiniAOD-00010	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	19971900	JME-RunIISummer19UL17MiniAOD-00011	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	19971900	JME-RunIISummer19UL17MiniAOD-00012	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	19888800	JME-RunIISummer19UL17MiniAOD-00013	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00001	submitted
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00002	submitted
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00003	approved
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00007	approved
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00008	new
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00009	approved
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00010	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00012	done
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00013	submitted
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00014	approved
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00015	new
QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8	19992900	JME-RunIISummer19UL18MiniAOD-00016	done
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00021	new
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00022	new
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00023	approved
QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8	20000000	JME-RunIISummer19UL18MiniAOD-00024	done
QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	40845133	HIG-RunIISummer19UL17MiniAOD-00152	done
QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	40414288	HIG-RunIISummer19UL18MiniAOD-00170	done
QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	76843234	HIG-RunIISummer19UL18MiniAOD-00003	done
QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	80882881	HIG-RunIISummer19UL17MiniAOD-00172	done
QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	57878016	HIG-RunIISummer19UL17MiniAOD-00161	done
QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	57455983	HIG-RunIISummer19UL18MiniAOD-00171	done
QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	57882249	HIG-RunIISummer19UL17MiniAOD-00157	done
QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	57514814	HIG-RunIISummer19UL18MiniAOD-00172	done
QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	59756602	HIG-RunIISummer19UL18MiniAOD-00173	done
QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	59889347	HIG-RunIISummer19UL17MiniAOD-00164	done
QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	47696443	HIG-RunIISummer19UL17MiniAOD-00173	done
QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	47758018	HIG-RunIISummer19UL18MiniAOD-00174	submitted
QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	15717983	HIG-RunIISummer19UL18MiniAOD-00175	done
QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	15751541	HIG-RunIISummer19UL17MiniAOD-00158	done
QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	10655313	HIG-RunIISummer19UL18MiniAOD-00176	done
QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	10645844	HIG-RunIISummer19UL17MiniAOD-00159	done
QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	5497202	HIG-RunIISummer19UL18MiniAOD-00177	done
QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8	5502712	HIG-RunIISummer19UL17MiniAOD-00156	done
````

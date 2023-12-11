#!/usr/bin/env python3
import os
import sys
import argparse
import textwrap
import math

parser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
    description=textwrap.dedent('''\
            ------------------------------------------------
               This script checks for possible WARNINGs and ERRORs
               and does a patch for the MG5_aMC LO nthreads problem if needed.
                                                                                    '''))
parser.add_argument('--mass', type=str, help="input charged higgs mass", nargs='+')
parser.add_argument('--proc', type=str, help="enter process cgbh or bgth", nargs='+')
args = parser.parse_args()

mass = 0
proc = {}
inputgpdir = {}

if args.mass is not None:
	mass = int(args.mass[0])
else:
	print("Input charged higgs mass e.g. --mass 400")
	sys.exit()
if args.proc is not None:
	proc = args.proc[0]
else:
	print("Input process: cgbh or bhth. e.g. --proc cgth")
	sys.exit()

cgbh_highmass= "/cvmfs/cms.cern.ch/phys_generator/gridpacks/slc7_amd64_gcc700/13TeV/madgraph/V5_2.6.5/cgbh-new/"
bgth_highmass= "/cvmfs/cms.cern.ch/phys_generator/gridpacks/slc7_amd64_gcc700/13TeV/madgraph/V5_2.6.5/bgth-new/"
cgbh_lowmass = "/cvmfs/cms.cern.ch/phys_generator/gridpacks/UL/13TeV/madgraph/V5_2.6.5/g2HDM/cgbh/"
bgth_lowmass = "/cvmfs/cms.cern.ch/phys_generator/gridpacks/UL/13TeV/madgraph/V5_2.6.5/g2HDM/bgth/"

if mass < 750:
	if proc == "cgbh":
		inputgpdir = cgbh_lowmass
	if proc == "bgth":
		inputgpdir = bgth_lowmass
else:
	if proc == "cgbh":
		inputgpdir = cgbh_highmass
	if proc == "bgth":
		inputgpdir = bgth_highmass	


weight = 1./16.
grid_points = "grid_points = ["
for file in os.listdir(inputgpdir):
	if "M"+str(mass) in file and "CMSSW_10_6_19_" not in file: 
		index = file.find("rhott")
		coupling = file[index:index+15].replace("_","-")
		if proc == "cgbh":
			dataset_name = "CGToBHpm_MH-"+str(mass)+"-"+coupling+"_TuneCP5_13TeV_G2HDM-madgraphMLM-pythia8"
		if proc == "bgth":
			dataset_name = "BGToTHpm_MH-"+str(mass)+"-"+coupling+"_TuneCP5_13TeV_G2HDM-madgraphMLM-pythia8"	
		print(dataset_name)
		grid_points += "{\"gridpack_path\": \""+inputgpdir+file+"\""+",\"processParameters\":"+\
					  "['JetMatching:setMad = off',"+\
					  "'JetMatching:scheme = 1',"+\
					  "'JetMatching:merge = on',"+\
            		  "'JetMatching:jetAlgorithm = 2',"+\
            		  "'JetMatching:etaJetMax = 5.',"+\
                      "'JetMatching:coneRadius = 1.',"+\
                      "'JetMatching:slowJetPower = 1',"+\
                      "'JetMatching:qCut = 45.',"+\
                      "'JetMatching:nQmatch = 5',"+\
                      "'JetMatching:nJetMax = 2',"+\
                      "'JetMatching:doShowerKt = off'"+\
			          "], \"name\": \""+dataset_name+"\", \"weight\":"+str(weight)+"}, "
grid_points = grid_points[::-1].replace(", "[::-1],"]\n"[::-1],1)[::-1]
fragment = """
import FWCore.ParameterSet.Config as cms

from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *
from Configuration.Generator.PSweightsPythia.PythiaPSweightsSettings_cfi import *

generator = cms.EDFilter("Pythia8GeneratorFilter",
	maxEventsToPrint = cms.untracked.int32(1),
	pythiaPylistVerbosity = cms.untracked.int32(1),
	filterEfficiency = cms.untracked.double(1.0),
	pythiaHepMCVerbosity = cms.untracked.bool(False),
	comEnergy = cms.double(13000.),
	RandomizedParameters = cms.VPSet(),
)"""


fragment += "\n\n"+grid_points
fragment += r"""
for grid_point in grid_points:
	basePythiaParameters = cms.PSet(
		pythia8CommonSettingsBlock,
		pythia8CP5SettingsBlock,
		pythia8PSweightsSettingsBlock,
		processParameters = cms.vstring(grid_point['processParameters']),
		parameterSets = cms.vstring(
			"pythia8CommonSettings",
			"pythia8CP5Settings",
			"pythia8PSweightsSettings",
			'processParameters',
		),
	)

	generator.RandomizedParameters.append(
		cms.PSet(
			ConfigWeight = cms.double(grid_point['weight']),
			ConfigDescription = cms.string(grid_point['name']),
			PythiaParameters = basePythiaParameters,
			GridpackPath = cms.string(grid_point['gridpack_path']),
		)
	)

ProductionFilterSequence = cms.Sequence(generator)"""
dataset_name = dataset_name.replace("-"+coupling,"")
frag_file_name = "fragment_"+dataset_name+".txt"
with open(frag_file_name,'w') as f:
	print(fragment,file=f)

#eventsPerLS_min = math.floor(min_nevents / 100.)
#eventsPerLS_max = math.floor(max_nevents / 1000.)
#if eventsPerLS_min < 100:
#   print ("WARNING : Min nEvents = {} => eventsPerLS = {} is below 100".format(min_nevents, eventsPerLS_min))
#   eventsPerLS_min = 100
#if eventsPerLS_max > 1000:
#   print ("WARNING : Min nEvents = {} => eventsPerLS = {} is above 1000".format(min_nevents, eventsPerLS_max))
#   eventsPerLS = 1000
#
#eventsPerLS = min(max(100, eventsPerLS), 1000)
#print("Events per Lumi Section=",eventsPerLS)

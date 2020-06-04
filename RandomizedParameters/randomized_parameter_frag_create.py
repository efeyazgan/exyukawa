#!/usr/bin/env python3
import os
import sys
import csv
import pickle
import math

#min_nevents = 1.e20
#max_nevents = 0.0
grid_points = "grid_points = ["
with open('TOP_MC_Request_Information_g2HDM_2020_Sheet1.csv',newline='') as csvf:
	csvreader = csv.DictReader(csvf,delimiter=' ')
	for row in csvreader:
		if float(row['Total_events']) < min_nevents:
			min_nevents = float(row['Total_events'])
		if float(row['Total_events']) > max_nevents:
			max_nevents = float(row['Total_events'])
		grid_points += "{\"gridpack_path\": \""+row['Gridpack_location']+"\""+",\"processParameters\":"+\
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
			          "], \"name\": \""+row['Dataset_name']+"\", \"weight\":"+row['Weight']+"}, "
	grid_points = grid_points[:-2]+"]\n"
#	print(grid_points)

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
	with open("fragment.txt",'w') as f:
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

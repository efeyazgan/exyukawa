import csv

grid_points = "grid_points = ["
with open('TOP_MC_Request_Information_g2HDM_2020_Sheet1.csv',newline='') as csvf:
	csvreader = csv.DictReader(csvf,delimiter=' ')
	for row in csvreader:
#		print(row['Dataset_name'],row['Total_events'],row['Gridpack_location'],row['Weight'])
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


	fragment += grid_points
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
	print(fragment)


#grid_points = [{"gridpack_path": "/cvmfs/cms.cern.ch/phys_generator/gridpacks/2017/13TeV/madgraph/V5_2.6.1/ttbarDM_inclusive_DMsimp_LO/ttbarDM__dilepton__DMsimp_LO_ps_spin0__mchi_1_mphi_50_gSM_1_gDM_1_6500GeV_slc6_amd64_gcc630_CMSSW_9_3_8_tarball.tar.xz",
#"processParameters": ["JetMatching:setMad = off", "JetMatching:scheme = 1", "JetMatching:merge = on", "JetMatching:jetAlgorithm = 2", "JetMatching:etaJetMax = 5.", "JetMatching:coneRadius = 1.", "JetMatching:slowJetPower = 1", "JetMatching:qCut = 90", "JetMatching:nQmatch = 5", "JetMatching:nJetMax = 1", "JetMatching:doShowerKt = off", "Check:epTolErr = 0.0003",
#"SLHA:minMassSM = 0.1"], "name": "/TTbarDMJets_Dilepton_pseudoscalar_LO_Mchi-1_Mphi-50_TuneCP5_13TeV-madgraph-mcatnlo-pythia8", "weight": 0.10059171597633136}

from CRABClient.UserUtilities import config
config = config()

config.General.requestName = '__REQUEST_NAME__'
inputList='__INPUT_FILE_LIST__'
config.Data.userInputFiles = open(inputList).readlines()
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.pyCfgParams = ['noprint']
config.JobType.psetName = 'recoPbPbrawPr2mini_RAW2DIGI_L1Reco_RECO_PAT_T4.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 4
config.JobType.maxMemoryMB = 10000
config.JobType.maxJobRuntimeMin = 480

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.outLFNDirBase = '__OUTPUT_DIR__'
config.Data.publication = False

config.Site.storageSite = 'T2_CH_CERN'
config.Site.whitelist = ['T2_CH_CERN']

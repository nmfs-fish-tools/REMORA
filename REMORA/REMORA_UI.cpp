#include "REMORA_UI.h"



REMORA_UI::REMORA_UI(
        QWidget*     parentW,
        nmfDatabase* databasePtr,
        nmfLogger*   logger,
        std::string& projectDir,
        std::string& projectName,
        std::string& modelName,
        QStringList& SpeciesList)
{
    m_DatabasePtr            = databasePtr;
    m_Logger                 = logger;
    m_ProjectDir             = projectDir;
    m_ProjectName            = projectName;
    m_ModelName              = modelName;
    m_ScenarioChanged        = false;
    m_MaxYAxis               = -1.0;
    m_HarvestType            = "ForecastHarvestCatch";
    m_NumYearsPerRun         = 20;
    m_NumRunsPerForecast     = 10;
    m_IndexMaxYScaleFactor   =  0;
    m_IndexScaleFactorChart1 =  0;
    m_IndexScaleFactorChart2 = -1;
    m_IndexScaleFactorPoint  =  0;
    m_TopLevelWidget         = loadUI(parentW);

    MModeYearsPerRunSL       = m_TopLevelWidget->findChild<QSlider*     >("MModeYearsPerRunSL");
    MModeRunsPerForecastSL   = m_TopLevelWidget->findChild<QSlider*     >("MModeRunsPerForecastSL");
    MModeScenarioNameLE      = m_TopLevelWidget->findChild<QLineEdit*   >("MModeScenarioNameLE");
    MModeYearsPerRunLE       = m_TopLevelWidget->findChild<QLineEdit*   >("MModeYearsPerRunLE");
    MModeRunsPerForecastLE   = m_TopLevelWidget->findChild<QLineEdit*   >("MModeRunsPerForecastLE");
    MModePctMSYLE            = m_TopLevelWidget->findChild<QLineEdit*   >("MModePctMSYLE");
    MModeRParamLE            = m_TopLevelWidget->findChild<QLineEdit*   >("MModeRParamLE");
    MModeKParamLE            = m_TopLevelWidget->findChild<QLineEdit*   >("MModeKParamLE");
    MModeHParamLE            = m_TopLevelWidget->findChild<QLineEdit*   >("MModeHParamLE");
    MModePctMSYDL            = m_TopLevelWidget->findChild<QDial*       >("MModePctMSYDL");
    MModeRParamDL            = m_TopLevelWidget->findChild<QDial*       >("MModeRParamDL");
    MModeKParamDL            = m_TopLevelWidget->findChild<QDial*       >("MModeKParamDL");
    MModeHParamDL            = m_TopLevelWidget->findChild<QDial*       >("MModeHParamDL");
    MModeSpeciesCMB          = m_TopLevelWidget->findChild<QComboBox*   >("MModeSpeciesCMB");
    MModeSpeciesLB           = m_TopLevelWidget->findChild<QLabel*      >("MModeSpeciesLB");
    MModeUpperPlotWidget     = m_TopLevelWidget->findChild<QWidget*     >("MModeUpperPlotWidget");
    MModeHarvestChartWidget  = m_TopLevelWidget->findChild<QWidget*     >("MModeHarvestChartWidget");
    MModeWindowWidget        = m_TopLevelWidget->findChild<QWidget*     >("MModeWindowWidget");
    MModeParentChartW        = m_TopLevelWidget->findChild<QWidget*     >("MModeParentChartW");
    MModeForecastRunPB       = m_TopLevelWidget->findChild<QPushButton* >("MModeForecastRunPB");
    MModeForecastLoadPB      = m_TopLevelWidget->findChild<QPushButton* >("MModeForecastLoadPB");
    MModeForecastSavePB      = m_TopLevelWidget->findChild<QPushButton* >("MModeForecastSavePB");
    MModeForecastDelPB       = m_TopLevelWidget->findChild<QPushButton* >("MModeForecastDelPB");
    MModeMultiPlotTypePB     = m_TopLevelWidget->findChild<QPushButton* >("MModeMultiPlotTypePB");
    MModeMaxScaleFactorPB    = m_TopLevelWidget->findChild<QPushButton* >("MModeMaxScaleFactorPB");
    MModeShowMSYCB           = m_TopLevelWidget->findChild<QCheckBox*   >("MModeShowMSYCB");
    MModePctMSYCB            = m_TopLevelWidget->findChild<QCheckBox*   >("MModePctMSYCB");
    MModeDeterministicRB     = m_TopLevelWidget->findChild<QRadioButton*>("MModeDeterministicRB");
    MModeStochasticRB        = m_TopLevelWidget->findChild<QRadioButton*>("MModeStochasticRB");
    MModePlotTypeSSRB        = m_TopLevelWidget->findChild<QRadioButton*>("MModePlotTypeSSRB");
    MModePlotTypeMSRB        = m_TopLevelWidget->findChild<QRadioButton*>("MModePlotTypeMSRB");
//  MModeHarvestTypePB       = m_TopLevelWidget->findChild<QPushButton* >("MModeHarvestTypePB");
    MModeHarvestTypeLBL      = m_TopLevelWidget->findChild<QLabel*      >("MModeHarvestTypeLBL");
    MModePctMSYLBL           = m_TopLevelWidget->findChild<QLabel*      >("MModePctMSYLBL");
    MModeForecastPlotTypeCMB = m_TopLevelWidget->findChild<QComboBox*   >("MModeForecastPlotTypeCMB");
    MModePlotScaleFactorCMB  = m_TopLevelWidget->findChild<QComboBox*   >("MModePlotScaleFactorCMB");
    InitializeScaleFactors();
    MModeForecastPlotTypeLB  = m_TopLevelWidget->findChild<QLabel*      >("MModeForecastPlotTypeLB");
    MModeYAxisLockCB         = m_TopLevelWidget->findChild<QCheckBox*   >("MModeYAxisLockCB");
    MModeForecastTypeLB      = m_TopLevelWidget->findChild<QLabel*      >("MModeForecastTypeLB");
    MModePlotTypeLB          = m_TopLevelWidget->findChild<QLabel*      >("MModePlotTypeLB");
    MModePlotScaleFactorLBL  = m_TopLevelWidget->findChild<QLabel*      >("MModePlotScaleFactorLBL");
    MModePlotScaleFactorLBL->setToolTip("Sets the scale of y-axis");
    MModePlotScaleFactorLBL->setStatusTip("Sets the scale of y-axis");
    MModeKParamLB            = m_TopLevelWidget->findChild<QLabel*      >("MModeKParamLB");
    MModeKPctLB              = m_TopLevelWidget->findChild<QLabel*      >("MModeKPctLB");

    MModeDeterministicRB->setChecked(false);
    MModeStochasticRB->setChecked(true);
    MModePlotTypeSSRB->setChecked(true);
    MModePlotTypeMSRB->setChecked(false);
    MModeMultiPlotTypePB->setEnabled(false);
    MModeYearsPerRunSL->setPageStep(1);
    MModeRunsPerForecastSL->setPageStep(1);
    MModeHParamDL->setPageStep(1);
    MModeRParamDL->setPageStep(1);
    MModeKParamDL->setPageStep(1);
    MModePctMSYDL->setPageStep(1);

    // Setting the dials to their default values
    MModePctMSYDL->setValue(110);
    MModePctMSYLE->setText("110");
    MModeRParamDL->setValue(0);
    MModeKParamDL->setValue(0);
    MModeHParamDL->setValue(0);
    MModePctMSYLE->setEnabled(false);
    MModePctMSYDL->setEnabled(false);
    MModePctMSYLBL->setEnabled(false);

    //Defaulting the sliders to their lowest values
    MModeYearsPerRunSL->setValue(m_NumYearsPerRun);
    MModeRunsPerForecastSL->setValue(m_NumRunsPerForecast);

    //Setting the paired line edits to the lowest values of their respective widgets
    MModeYearsPerRunLE->setText(QString::number(m_NumYearsPerRun));
    MModeRunsPerForecastLE->setText(QString::number(m_NumRunsPerForecast));
    MModeRParamLE->setText(QString::number(0));
    MModeKParamLE->setText(QString::number(0));
    MModeHParamLE->setText(QString::number(0));

    // Setup chart widgets
    m_ChartWidget     = new QChart();
    m_ChartView       = new QChartView(m_ChartWidget);
    m_VLayt           = new QVBoxLayout();
    m_GridVLayt       = new QVBoxLayout();
    m_GridLayt        = new QGridLayout();
    m_GridParent      = new QWidget();
    QLabel* gridTitle = new QLabel("Forecast Runs for All Species");
    m_ForecastLineChartMonteCarlo = new nmfChartLine();
    m_ForecastBiomassLineChart    = new nmfChartLine();
    m_ForecastHarvestLineChart    = new nmfChartLine();
    m_MSYLineChart                = new nmfChartLine();
    QFont font = gridTitle->font();
    font.setPixelSize(font.pixelSize()+20);
    font.setWeight(QFont::Bold);
    gridTitle->setFont(font);
    gridTitle->setAlignment(Qt::AlignHCenter);
    m_GridVLayt->addWidget(gridTitle);
    m_GridVLayt->addLayout(m_GridLayt);
    m_GridParent->setLayout(m_GridVLayt);
    m_VLayt->addWidget(m_ChartView);
    MModeUpperPlotWidget->setLayout(m_VLayt);

    // Setup Remora's forecast directory
    m_RemoraScenarioDir = QDir(QString::fromStdString(m_ProjectDir)).filePath(
                               QString::fromStdString(nmfConstantsMSSPM::OutputScenariosDirMMode));
    QDir().mkdir(m_RemoraScenarioDir); // Makes the directory if it doesn't already exist

    // Setup function map for setters
    m_FunctionMap["Forecast"]             = &REMORA_UI::setScenarioName;
    m_FunctionMap["NumYearsPerRun"]       = &REMORA_UI::setNumYearsPerRun;
    m_FunctionMap["NumRunsPerForecast"]   = &REMORA_UI::setNumRunsPerForecast;
    m_FunctionMap["isDeterministic"]      = &REMORA_UI::setDeterministic;
    m_FunctionMap["isSingleSpecies"]      = &REMORA_UI::setSingleSpecies;
    m_FunctionMap["isMultiPlot"]          = &REMORA_UI::setMultiPlot;
    m_FunctionMap["ForecastDataType"]     = &REMORA_UI::setForecastPlotType;
    m_FunctionMap["isMSYLineVisible"]     = &REMORA_UI::setMSYLineVisible;
    m_FunctionMap["r_Uncertainty"]        = &REMORA_UI::setUncertaintyGrowth;
    m_FunctionMap["K_Uncertainty"]        = &REMORA_UI::setUncertaintyCarryingCapacity;
    m_FunctionMap["HarvestType"]          = &REMORA_UI::setHarvestType;
    m_FunctionMap["H_Uncertainty"]        = &REMORA_UI::setUncertaintyHarvest;
    m_FunctionMap["MaxYScaleFactor"]      = &REMORA_UI::setMaxYScaleFactor;
    m_FunctionMap["NumScaleFactorPoints"] = &REMORA_UI::setNumScaleFactorPoints;
    m_FunctionMap["point"]                = &REMORA_UI::setAScaleFactorPoint;

    setupMovableLineCharts(SpeciesList);
    setupConnections();
    enableWidgets(false);

}

REMORA_UI::~REMORA_UI()
{

}

void
REMORA_UI::setModelName(std::string modelName)
{
    m_ModelName = modelName;
}

bool
REMORA_UI::couldShowMSYCB()
{
    return (isSingleSpecies() || (isMultiSpecies() && isMultiPlot()));
}

void
REMORA_UI::drawMultiSpeciesChart()
{
    bool isFishingMortality = isFishingMortalityPlotType();
    bool isAbsoluteBiomass  = isAbsoluteBiomassPlotType();
    bool isRelativeBiomass  = isRelativeBiomassPlotType();
    int StartForecastYear;
    int StartYear;
    int EndYear;
    int NumSpecies;
    int NumObservedYears;
    int LastHarvestYear    = 0;
    int NumYearsPerRun     = getNumYearsPerRun();
    int NumRunsPerForecast = getNumRunsPerForecast();
    int SpeciesNum         =  -1;
    int Theme              =   0;
    double YMinVal  = 0;
    double YMaxVal  = nmfConstants::NoValueDouble;
    double ScaleVal = getPlotScaleFactor();
    double HarvestValue;
    double remTime0Value  = 0;
    std::string ChartType = "Line";
    std::string LineStyle = "SolidLine";
    std::string msg;
    std::string Algorithm;
    std::string Minimizer;
    std::string ObjectiveCriterion;
    std::string Scaling;
    std::string TableName = "Forecasts";
    std::string MainTitle = "Forecast Runs for All Species";
    std::string XLabel    = "Year";
    std::string YLabel;
    QStringList RowLabelsForBars;
    QStringList ColumnLabelsForLegend;
    QStringList ColumnLabelsForLegendMSY;
    QStringList HoverLabels;
    boost::numeric::ublas::matrix<double> ChartLine;
    boost::numeric::ublas::matrix<double> Harvest;
    std::vector<std::string> SpeNames;
    std::vector<bool> GridLines = {true,true};
    std::vector<boost::numeric::ublas::matrix<double> > ForecastBiomass;
    QList<QColor> LineColors;

    LineColors.append(QColor(nmfConstants::LineColors[0].c_str()));

    getYearRange(StartYear,EndYear);
    NumObservedYears  = EndYear - StartYear;
    StartForecastYear = EndYear;

    m_DatabasePtr->getAllSpecies(m_Logger,SpeNames);
    for (std::string species : SpeNames) {
        ColumnLabelsForLegend    << QString::fromStdString(species);
        HoverLabels              << QString::fromStdString(species);
        ColumnLabelsForLegendMSY << "MSY";
    }
    HoverLabels = ColumnLabelsForLegend;
    NumSpecies = SpeNames.size();

    if (isFishingMortality) {
        YLabel = nmfConstantsMSSPM::OutputChartExploitationCatchTitle.toStdString();
        if (! m_DatabasePtr->getTimeSeriesData(
                    m_TopLevelWidget,m_Logger,m_ProjectName,m_ModelName,"",
                    QString::fromStdString(m_HarvestType).replace("Forecast","").toStdString(),
                    NumSpecies,NumObservedYears,Harvest)) {
            return;
        }
        LastHarvestYear = Harvest.size1()-1;
    } else if (isAbsoluteBiomass) {
        YLabel = "Biomass (" + getYLBLPlotScaleFactor(ScaleVal).toStdString() + "metric tons)";
    } else if (isRelativeBiomass) {
        YLabel = "Relative Biomass";
    }

    ChartLine.resize(NumYearsPerRun+1,NumSpecies);
    ChartLine.clear();

    if (! m_DatabasePtr->getForecastInfo(
         TableName,m_ProjectName,m_ForecastName,NumYearsPerRun,StartForecastYear,
         Algorithm,Minimizer,ObjectiveCriterion,Scaling,NumRunsPerForecast)) {
        return;
    }

    // Plot ForecastBiomass data
    if (! m_DatabasePtr->getForecastBiomass(
                m_TopLevelWidget,m_Logger,m_ProjectName,m_ForecastName,
                NumSpecies,NumYearsPerRun,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                ForecastBiomass)) {
        return;
    }

    // Get ChartLine Data (Forecast Biomass data without any stochasticity)
    for (int species=0; species<NumSpecies; ++species) {
        for (int time=0; time<=NumYearsPerRun; ++time) {
            if (isFishingMortality) {
                HarvestValue = m_MovableLineCharts[species]->getYValue(time) * Harvest(LastHarvestYear,species);
                if (nmfUtils::isNearlyZero(ForecastBiomass[0](time,species))) {
                    ChartLine(time,species) = nmfConstantsMSSPM::NoFishingMortality;
//                  msg = "Found MS Biomass = 0, setting F to 0 for Species: " +
//                         SpeNames[species] + " at Year = " + std::to_string(time+StartForecastYear);
//                  m_Logger->logMsg(nmfConstants::Warning,msg);
                } else {
                    ChartLine(time,species) = HarvestValue/ForecastBiomass[0](time,species);
                }
            } else {
                ChartLine(time,species) = ForecastBiomass[0](time,species)/ScaleVal;
                if (isRelativeBiomass) {
                    if (time == 0) {
                        remTime0Value = ChartLine(0,species);
                    }
                    if (nmfUtils::isNearlyZero(remTime0Value)) {
                        msg = "Found first year Biomass = 0, setting relative Biomass to 0 for Species: " +
                               SpeNames[species] + " at Year = " + std::to_string(time+StartForecastYear);
                        m_Logger->logMsg(nmfConstants::Warning,msg);
                        ChartLine(time,species) = 0;
                    } else {
                        ChartLine(time,species) /= remTime0Value;
                    }
                }
            }
        }
    }

    m_GridParent->hide();
    m_ChartView->show();

    m_ForecastHarvestLineChart->populateChart(
                m_ChartWidget,
                ChartType,
                LineStyle,
                nmfConstantsMSSPM::ShowFirstPoint,
                nmfConstants::ShowLegend,
                StartForecastYear,
                nmfConstantsMSSPM::LabelXAxisAsInts,
                YMinVal,YMaxVal,
                nmfConstantsMSSPM::LeaveGapsWhereNegative,
                ChartLine,
                RowLabelsForBars,
                ColumnLabelsForLegend,
                HoverLabels,
                MainTitle,
                XLabel,
                YLabel,
                GridLines,
                Theme,
                LineColors[0],
                "MultiSpecies",
                1.0);

    removeMSYLines(m_ChartWidget,{"MSY = r/2","MSY = K/2"});
    removeMSYLines(m_ChartWidget,{"MSY = % of r/2","MSY = % of K/2"});
    if (isMSYBoxChecked()) {
        drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                     StartForecastYear,YMinVal,YMaxVal,
                     Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                     RowLabelsForBars,ColumnLabelsForLegendMSY,HoverLabels,
                     MainTitle,XLabel,YLabel,nmfConstants::ShowLegend,1.0);
    }
    if (isPctMSYBoxChecked()) {
        drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                     // NumRunsPerForecast,NoUncertaintyRun,
                     StartForecastYear,YMinVal,YMaxVal,
                     Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                     RowLabelsForBars,ColumnLabelsForLegendMSY,HoverLabels,
                     MainTitle,XLabel,YLabel,nmfConstants::ShowLegend,getPctMSYValue());
    }

}

void
REMORA_UI::drawMSYLines()
{
    int StartYear;
    int EndYear;
    int NumSpecies;
    int StartForecastYear;
    double YMinVal         = 0;
    double YMaxVal         = nmfConstants::NoValueDouble;
    int NumYearsPerRun     = getNumYearsPerRun();
    int NumRunsPerForecast = getNumRunsPerForecast();
    int SpeciesNum         = getSpeciesNum();
    std::string XLabel     = "Year";
    std::string YLabel     = "Biomass ("+ getYLBLPlotScaleFactor(getPlotScaleFactor()).toStdString() +"metric tons)";
    std::string MainTitle  = "Forecast Run for Species: ";
    std::string Algorithm;
    std::string Minimizer;
    std::string ObjectiveCriterion;
    std::string Scaling;
    std::string TableName = "Forecasts";
    std::vector<std::string> SpeNames;
    QStringList RowLabelsForBars;
    QStringList HoverLabels;
    QStringList HoverLabelsPct;
    QStringList ColumnLabelsForLegendMSY;
    QStringList ColumnLabelsForLegendPctMSY;

    getYearRange(StartYear,EndYear);
    StartForecastYear = EndYear;

    m_DatabasePtr->getAllSpecies(m_Logger,SpeNames);
    NumSpecies = SpeNames.size();
    MainTitle += SpeNames[SpeciesNum];

    if (! m_DatabasePtr->getForecastInfo(
                TableName,m_ProjectName,m_ForecastName,NumYearsPerRun,StartForecastYear,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,NumRunsPerForecast)) {
        return;
    }

    if (isSingleSpecies()) {

        if (isMSYBoxChecked()) {
            HoverLabels.clear();
            ColumnLabelsForLegendMSY.clear();
            if (isAbsoluteBiomassPlotType()) {
                HoverLabels << "MSY = K/2";
                ColumnLabelsForLegendMSY << "MSY = K/2";
            } else if (isFishingMortalityPlotType()) {
                HoverLabels << "MSY = r/2";
                ColumnLabelsForLegendMSY << "MSY = r/2";
            }
            drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                         StartForecastYear,YMinVal,YMaxVal,
                         Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                         RowLabelsForBars,ColumnLabelsForLegendMSY,HoverLabels,
                         MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,1.0);
        }
        if (isPctMSYBoxChecked()) {
            HoverLabelsPct.clear();
            ColumnLabelsForLegendPctMSY.clear();
            if (isAbsoluteBiomassPlotType()) {
                HoverLabelsPct << "MSY = % of K/2";
                ColumnLabelsForLegendPctMSY << "MSY = % of K/2";
            } else if (isFishingMortalityPlotType()) {
                HoverLabelsPct << "MSY = % of r/2";
                ColumnLabelsForLegendPctMSY << "MSY = % of r/2";
            }
            drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                         StartForecastYear,YMinVal,YMaxVal,
                         Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                         RowLabelsForBars,ColumnLabelsForLegendPctMSY,HoverLabelsPct,
                         MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,getPctMSYValue());
        }
        qobject_cast<QValueAxis*>(m_ChartWidget->axes(Qt::Vertical).back())->setTickCount(5);

    } else if (isMultiPlot()) {
        SpeciesNum =  0;
        if (isAbsoluteBiomassPlotType()) {
            YLabel = "Biomass ("+getYLBLPlotScaleFactor(getPlotScaleFactor()).toStdString() + "mt)";
        } else if (isRelativeBiomassPlotType()) {
            YLabel = "Rel Biomass";
        } else if (isFishingMortalityPlotType()) {
            YLabel = "F Mortality (C/Bc)";
        }
        for (QChart* chart : m_Charts) {
            MainTitle  =  SpeNames[SpeciesNum];
            if (isMSYBoxChecked()) {
                HoverLabels.clear();
                ColumnLabelsForLegendMSY.clear();
                if (isAbsoluteBiomassPlotType()) {
                    HoverLabels << "MSY = K/2";
                    ColumnLabelsForLegendMSY << "MSY = K/2";
                } else if (isFishingMortalityPlotType()) {
                    HoverLabels << "MSY = r/2";
                    ColumnLabelsForLegendMSY << "MSY = r/2";
                }
                drawMSYLines(chart,SpeciesNum,NumSpecies,NumYearsPerRun,
                             StartForecastYear,YMinVal,YMaxVal,
                             Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                             RowLabelsForBars,ColumnLabelsForLegendMSY,HoverLabels,
                             MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,1.0);
            }
            if (isPctMSYBoxChecked()) {
                HoverLabelsPct.clear();
                ColumnLabelsForLegendPctMSY.clear();
                if (isAbsoluteBiomassPlotType()) {
                    HoverLabelsPct << "MSY = % of K/2";
                    ColumnLabelsForLegendPctMSY << "MSY = % of K/2";
                } else if (isFishingMortalityPlotType()) {
                    HoverLabelsPct << "MSY = % of r/2";
                    ColumnLabelsForLegendPctMSY << "MSY = % of r/2";
                }
                drawMSYLines(chart,SpeciesNum,NumSpecies,NumYearsPerRun,
                             StartForecastYear,YMinVal,YMaxVal,
                             Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                             RowLabelsForBars,ColumnLabelsForLegendPctMSY,HoverLabelsPct,
                             MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,getPctMSYValue());
            }
            qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).back())->setTickCount(5);
            ++SpeciesNum;
        }

    }

    resetXAxis();
}

void
REMORA_UI::drawMSYLines(
        QChart* chart,
        int& SpeciesNum,
        int& NumSpecies,
        int& NumYearsPerRun,
        int& StartForecastYear,
        double& YMinVal,
        double& YMaxVal,
        std::string& Algorithm,
        std::string& Minimizer,
        std::string& ObjectiveCriterion,
        std::string& Scaling,
        QStringList& RowLabelsForBars,
        QStringList& ColumnLabelsForLegend,
        QStringList& HoverData,
        std::string& MainTitle,
        std::string& XLabel,
        std::string& YLabel,
        const bool& ShowLegend,
        const double& Pct)
{
    bool isFishingMortality = (getForecastPlotType() == nmfConstantsMSSPM::OutputChartExploitation);
    int Theme = 0;
    double MSYValue;
    double ScaleVal = getPlotScaleFactor(); // 1.0
    std::string queryStr;
    std::string LineStyle    = "DashedLine";
    std::string ChartType    = "Line";
    std::string isAggProdStr = "0";
    boost::numeric::ublas::matrix<double> ChartMSYData;
    std::map<std::string, std::vector<std::string> > dataMap;
    std::vector<std::string> fields;
    std::vector<bool> GridLines = {true,true};
    QColor LineColor = QColor(nmfConstants::LineColors[0].c_str());

    if (Pct != 1.0) {
        LineStyle = "DottedLine";
    }

    std::string TableName = (isFishingMortality) ? "OutputMSYFishing" : "OutputMSYBiomass";
    if (SpeciesNum == -1) {
        ChartMSYData.resize(NumYearsPerRun+1,NumSpecies);
    } else {
        ChartMSYData.resize(NumYearsPerRun+1,1);
    }
    ChartMSYData.clear();

    fields     = {"Algorithm","Minimizer","ObjectiveCriterion","Scaling","isAggProd","SpeName","Value"};
    queryStr   = "SELECT Algorithm,Minimizer,ObjectiveCriterion,Scaling,isAggProd,SpeName,Value FROM " + TableName;
    queryStr  += " WHERE Algorithm = '"         + Algorithm +
                 "' AND Minimizer = '"          + Minimizer +
                 "' AND ObjectiveCriterion = '" + ObjectiveCriterion +
                 "' AND Scaling = '"            + Scaling +
                 "' AND isAggProd = "           + isAggProdStr +
                 "  ORDER by SpeName";

    dataMap = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
    int NumRecords = dataMap["SpeName"].size();
    if (NumRecords == 0) {
        m_Logger->logMsg(nmfConstants::Error, queryStr);
        return;
    }
    // Draw the MSY line
    for (int i=0; i<NumSpecies; ++i) {
        MSYValue = Pct*std::stod(dataMap["Value"][i])/ScaleVal;
        if (SpeciesNum == -1) {
            for (int j=0; j<=NumYearsPerRun; ++j) {
                ChartMSYData(j,i) = MSYValue;
            }
        } else {
            if (i == SpeciesNum) {
                for (int j=0; j<=NumYearsPerRun; ++j) {
                    ChartMSYData(j,0) = MSYValue;
                }
            }
        }
    }
    m_MSYLineChart->populateChart(
                chart,
                ChartType,
                LineStyle,
                nmfConstantsMSSPM::ShowFirstPoint,
                ShowLegend,
                StartForecastYear,
                nmfConstantsMSSPM::LabelXAxisAsInts,
                YMinVal,YMaxVal,
                nmfConstantsMSSPM::LeaveGapsWhereNegative,
                ChartMSYData,
                RowLabelsForBars,
                ColumnLabelsForLegend,
                HoverData,
                MainTitle,
                XLabel,
                YLabel,
                GridLines,
                Theme,
                LineColor,
                "MultiSpecies",
                1.0);
}

void
REMORA_UI::drawPlot()
{
    m_ForecastBiomassLineChart->clear(m_ChartWidget);
    m_ForecastHarvestLineChart->clear(m_ChartWidget);
    m_ForecastLineChartMonteCarlo->clear(m_ChartWidget);

    if (couldShowMSYCB()) {
        drawSingleSpeciesChart();
    } else {
        drawMultiSpeciesChart();
    }

    // Rescale axes of plot(s)
    resetXAxis();
    resetYAxis();
}

void
REMORA_UI::drawSingleSpeciesChart()
{
    bool isFishingMortality  = isFishingMortalityPlotType();
    bool isAbsoluteBiomass   = isAbsoluteBiomassPlotType();
    bool isRelativeBiomass   = isRelativeBiomassPlotType();
    int StartYear;
    int EndYear;
    int NumSpecies;
    int StartForecastYear;
    double YMinVal         = 0;
    double YMaxVal         = nmfConstants::NoValueDouble;
    int NumYearsPerRun     = getNumYearsPerRun();
    int NumRunsPerForecast = getNumRunsPerForecast();
    int SpeciesNum         = getSpeciesNum();
    int Theme = 0;
    int LastCatchYear      = 0;
    int NumObservedYears;
    double ScaleVal         = getPlotScaleFactor();
    double brightnessFactor = 0.2;
    double CatchValue;
    double remTime0Value    = 0;
    std::string TableName = "Forecasts";
    std::string ChartType = "Line";
    std::string LineStyle = "SolidLine";
    std::string MainTitle = "Forecast Run";
    std::string XLabel    = "Year";
    std::string YLabel    = "Biomass (" + getYLBLPlotScaleFactor(ScaleVal).toStdString() + "metric tons)";
    std::string Algorithm;
    std::string Minimizer;
    std::string ObjectiveCriterion;
    std::string Scaling;
    std::string CurrentSpecies;
    std::string msg;
    std::string MainTitleMultiPlot;
    std::string YLabelMultiPlot;
    QStringList RowLabelsForBars;
    QStringList ColumnLabelsForLegend;
    QStringList HoverData;
    QStringList HoverLabels;
    QStringList HoverLabelsPct;
    boost::numeric::ublas::matrix<double> ChartLine;
    boost::numeric::ublas::matrix<double> ChartLineSinglePlot;
    boost::numeric::ublas::matrix<double> ChartLinesMonteCarlo;
    boost::numeric::ublas::matrix<double> ChartLinesMonteCarloSinglePlot;
    std::vector<boost::numeric::ublas::matrix<double> > ChartLineMultiPlot;
    std::vector<boost::numeric::ublas::matrix<double> > ChartLinesMonteCarloMultiPlot;
    std::vector<boost::numeric::ublas::matrix<double> > ChartLineSpans;
    boost::numeric::ublas::matrix<double> Harvest;
    std::vector<bool> GridLines = {true,true};
    std::vector<boost::numeric::ublas::matrix<double> > ForecastBiomass;
    std::vector<boost::numeric::ublas::matrix<double> > ForecastBiomassMonteCarlo;
    std::vector<std::string> SpeNames;
    QList<QColor> LineColors;
    QColor dimmedColor = QColor(255-brightnessFactor*255,
                                255-brightnessFactor*255,
                                255-brightnessFactor*255);
    LineColors.append(QColor(nmfConstants::LineColors[0].c_str()));

    m_DatabasePtr->getAllSpecies(m_Logger,SpeNames);
    NumSpecies = SpeNames.size();
    CurrentSpecies = SpeNames[SpeciesNum];
    MainTitle += " for Species: " + CurrentSpecies;

    getYearRange(StartYear,EndYear);
    StartForecastYear = EndYear;
    NumObservedYears = EndYear-StartYear;

    if (isFishingMortality) {
        YLabel = nmfConstantsMSSPM::OutputChartExploitationCatchTitle.toStdString();
        if (! m_DatabasePtr->getTimeSeriesData(
                    m_TopLevelWidget,m_Logger,m_ProjectName,m_ModelName,"",
                    QString::fromStdString(m_HarvestType).replace("Forecast","").toStdString(),
                    NumSpecies,NumObservedYears,Harvest)) {
            return;
        }
        LastCatchYear = Harvest.size1()-1;
    } else if (isRelativeBiomass) {
        YLabel = "Relative Biomass";
    }

    if (! m_DatabasePtr->getForecastInfo(
         TableName,m_ProjectName,m_ForecastName,NumYearsPerRun,StartForecastYear,
         Algorithm,Minimizer,ObjectiveCriterion,Scaling,NumRunsPerForecast)) {
        return;
    }

    if (! m_DatabasePtr->getForecastBiomassMonteCarlo(
                m_TopLevelWidget,m_Logger,m_ProjectName,m_ForecastName,
                NumSpecies,NumYearsPerRun,NumRunsPerForecast,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                ForecastBiomassMonteCarlo)) {
        return;
    }

    // Plot ForecastBiomass data
    if (! m_DatabasePtr->getForecastBiomass(
                m_TopLevelWidget,m_Logger,m_ProjectName,m_ForecastName,
                NumSpecies,NumYearsPerRun,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                ForecastBiomass)) {
        return;
    }

    std::string currentSpecies = getCurrentSpecies();
    if (! m_DatabasePtr->getForecastMonteCarloParameters(
                m_TopLevelWidget,m_Logger,currentSpecies,m_ProjectName,m_ForecastName,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                HoverData)) {
        return;
    }

    ChartLinesMonteCarlo.resize(NumYearsPerRun+1,ForecastBiomassMonteCarlo.size());
    ChartLinesMonteCarlo.clear();
    ChartLine.resize(NumYearsPerRun+1,ForecastBiomass.size());
    ChartLine.clear();
    // NoUncertaintyRun = ForecastBiomass.size();

    // Get ChartLinesMonteCarlo Data
    for (int species=0; species<NumSpecies; ++species) {
        for (int line=0; line<NumRunsPerForecast; ++line) {
            for (int time=0; time<=NumYearsPerRun; ++time) {
                if (isFishingMortality) {
                    CatchValue = m_MovableLineCharts[species/*SpeciesNum*/]->getYValue(time) * Harvest(LastCatchYear,species);
                    if (nmfUtils::isNearlyZero(ForecastBiomassMonteCarlo[line](time,species))) {
                        ChartLinesMonteCarlo(time,line) = nmfConstantsMSSPM::NoFishingMortality;
//                       msg = "Found Monte Carlo Biomass = 0, setting F to 0 for Species: " +
//                              SpeNames[species] + " at Year = " + std::to_string(time+StartForecastYear);
//                       m_Logger->logMsg(nmfConstants::Warning,msg);
                    } else {
                        ChartLinesMonteCarlo(time,line) = CatchValue/(ForecastBiomassMonteCarlo[line](time,species));
                    }
                } else {
                    ChartLinesMonteCarlo(time,line) = ForecastBiomassMonteCarlo[line](time,species)/ScaleVal;
                    if (time == 0) {
                        remTime0Value = ChartLinesMonteCarlo(0,line);
                    }
                    if (isRelativeBiomass) {
                        if (nmfUtils::isNearlyZero(remTime0Value)) {
                            ChartLinesMonteCarlo(time,line) = 0;
                        } else {
                            ChartLinesMonteCarlo(time,line) /= remTime0Value;
                        }
                    }
                }
            }
        }

        if (species == SpeciesNum) {
            ChartLinesMonteCarloSinglePlot = ChartLinesMonteCarlo;
        }
        ChartLinesMonteCarloMultiPlot.push_back(ChartLinesMonteCarlo);
    }

    // Get ChartLineMultiPlot Data
    for (int species=0; species<NumSpecies; ++species) {
            for (int time=0; time<=NumYearsPerRun; ++time) {
                if (isFishingMortality) {
                    CatchValue = m_MovableLineCharts[species]->getYValue(time) * Harvest(LastCatchYear,species);
                    if (nmfUtils::isNearlyZero(ForecastBiomass[0](time,species))) {
                        ChartLine(time,0) = nmfConstantsMSSPM::NoFishingMortality;
//                      msg = "Found Biomass = 0, setting F to 0 for Species: " +
//                             SpeNames[species] + " at Year = " + std::to_string(time+StartForecastYear);
//                      m_Logger->logMsg(nmfConstants::Warning,msg);
                    } else {
                        ChartLine(time,0) = CatchValue/(ForecastBiomass[0](time,species));
                    }
                } else {
                    ChartLine(time,0) = ForecastBiomass[0](time,species)/ScaleVal;
                    if (time == 0) {
                        remTime0Value = ChartLine(0,0);
                    }
                    if (isRelativeBiomass) {
                        if (nmfUtils::isNearlyZero(remTime0Value)) {
                            ChartLine(time,0) = 0;
                        } else {
                            ChartLine(time,0) /= remTime0Value;
                        }
                    }
                }
            }
            if (species == SpeciesNum) {
                ChartLineSinglePlot = ChartLine;
            }
            ChartLineMultiPlot.push_back(ChartLine);
    }

    if (isMultiSpecies() && isMultiPlot()) {

        m_ChartView->hide();
        m_GridParent->show();

        m_Charts.clear();
        m_Views.clear();
        for (int i=0; i<NumSpecies; ++i) {
            m_Charts.append(new QChart());
            m_Views.append(new QChartView(m_Charts[i]));
        }

        // Test if perfect square
        long double root = sqrt(NumSpecies);
        bool perfectSquare = nmfUtils::isNearlyZero(root-std::floor(root));
        if (! perfectSquare) {
            root = std::floor(root+1);
        }
        int m = 0;
        bool done = false;
        for (int row=0; row<int(root); ++row) {
            if (done) break;
            m_GridLayt->setRowStretch(row,1);
            for (int col=0; col<int(root); ++col) {
                if (done) break;
                if (m < NumSpecies) {
                    if (row == 0) {
                        m_GridLayt->setColumnStretch(col,1);
                    }
                    m_GridLayt->addWidget(m_Views[m++],row,col);
                } else {
                    done = true;
                }
            }
        }
        m_VLayt->addWidget(m_GridParent);
        int species = 0;
        if (isFishingMortality) {
            YLabelMultiPlot = "F Mortality (C/Bc)";
        } else if (isAbsoluteBiomass) {
            YLabelMultiPlot = "Biomass ("+getYLBLPlotScaleFactor(getPlotScaleFactor()).toStdString() + "mt)";
        } else if (isRelativeBiomass) {
            YLabelMultiPlot = "Rel Biomass";
        }
        for (QChart* chart : m_Charts) {
            // This will set a chart background to a color. Revisit this logic if want to change the dark settings for a chart
            //chart->setBackgroundBrush(QBrush(QColor(100,100,100)));

            QMargins chartMargins(8, 10, 20, 10);
            m_ChartWidget->setMargins(chartMargins);

            // Draw forecast line(s)
            m_ChartWidget->removeAllSeries();

            // Draw stochastic forecast lines
            MainTitleMultiPlot =  SpeNames[species];
            m_ForecastLineChartMonteCarlo->clear(chart);

            // Split curve up into spans.  Gaps are where yvalue = -1.
            // Then iterate and call populateChart for each span.
            m_ForecastLineChartMonteCarlo->populateChart(
                        chart,
                        ChartType,
                        LineStyle,
                        nmfConstantsMSSPM::ShowFirstPoint,
                        nmfConstants::DontShowLegend,
                        StartForecastYear,
                        nmfConstantsMSSPM::LabelXAxisAsInts,
                        YMinVal,YMaxVal,
                        nmfConstantsMSSPM::LeaveGapsWhereNegative,
                        ChartLinesMonteCarloMultiPlot[species],
                        RowLabelsForBars,
                        ColumnLabelsForLegend,
                        HoverData,
                        MainTitleMultiPlot,
                        XLabel,
                        YLabelMultiPlot,
                        GridLines,
                        Theme,
                        dimmedColor,
                        "MonteCarloSimulation",
                        1.0);

            // Draw single line without any uncertainty variation
            m_ForecastBiomassLineChart->populateChart(
                        chart,
                        ChartType,
                        LineStyle,
                        nmfConstantsMSSPM::ShowFirstPoint,
                        nmfConstants::DontShowLegend,
                        StartForecastYear,
                        nmfConstantsMSSPM::LabelXAxisAsInts,
                        YMinVal,YMaxVal,
                        nmfConstantsMSSPM::LeaveGapsWhereNegative,
                        ChartLineMultiPlot[species],
                        RowLabelsForBars,
                        ColumnLabelsForLegend,
                        {HoverData[NumRunsPerForecast]},
                        MainTitleMultiPlot,
                        XLabel,
                        YLabelMultiPlot,
                        GridLines,
                        Theme,
                        LineColors[0],
                        "No Uncertainty Variations",
                        1.0);

            removeMSYLines(chart,{"MSY = r/2","MSY = K/2"});
            removeMSYLines(chart,{"MSY = % of r/2","MSY = % of K/2"});

            if (isMSYBoxChecked()) {
                HoverLabels.clear();
                if (isFishingMortality) {
                    HoverLabels << "MSY = r/2";
                } else if (isAbsoluteBiomass) {
                    HoverLabels << "MSY = K/2";
                } else if (isRelativeBiomass) {
                    HoverLabels << "";
                }
                drawMSYLines(chart,species,NumSpecies,NumYearsPerRun,
                             StartForecastYear,YMinVal,YMaxVal,
                             Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                             RowLabelsForBars,ColumnLabelsForLegend,HoverLabels,
                             MainTitleMultiPlot,XLabel,YLabelMultiPlot,
                             nmfConstants::DontShowLegend,1.0);
            }
            if (isPctMSYBoxChecked()) {
                HoverLabelsPct.clear();
                if (isFishingMortality) {
                    HoverLabelsPct << "MSY = % of r/2";
                } else if (isAbsoluteBiomass) {
                    HoverLabelsPct << "MSY = % of K/2";
                } else if (isRelativeBiomass) {
                    HoverLabelsPct << "";
                }
                drawMSYLines(chart,species,NumSpecies,NumYearsPerRun,
                             StartForecastYear,YMinVal,YMaxVal,
                             Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                             RowLabelsForBars,ColumnLabelsForLegend,HoverLabelsPct,
                             MainTitleMultiPlot,XLabel,YLabelMultiPlot,
                             nmfConstants::DontShowLegend,getPctMSYValue());
            }

            qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).back())->setTickCount(5);
            ++species;
        }

    }

    if (isSingleSpecies()) {

        m_GridParent->hide();
        m_ChartView->show();

        QMargins chartMargins(8, 10, 20, 10);
        m_ChartWidget->setMargins(chartMargins);

        // Draw forecast line(s)
        m_ChartWidget->removeAllSeries();

        // Draw stochastic forecast lines
        m_ForecastLineChartMonteCarlo->populateChart(
                    m_ChartWidget,
                    ChartType,
                    LineStyle,
                    nmfConstantsMSSPM::ShowFirstPoint,
                    nmfConstants::DontShowLegend,
                    StartForecastYear,
                    nmfConstantsMSSPM::LabelXAxisAsInts,
                    YMinVal,YMaxVal,
                    nmfConstantsMSSPM::LeaveGapsWhereNegative,
                    ChartLinesMonteCarloSinglePlot,
                    RowLabelsForBars,
                    ColumnLabelsForLegend,
                    HoverData,
                    MainTitle,
                    XLabel,
                    YLabel,
                    GridLines,
                    Theme,
                    dimmedColor,
                    "MonteCarloSimulation",
                    1.0);

        // Draw single line without any uncertainty variation
        m_ForecastBiomassLineChart->populateChart(
                    m_ChartWidget,
                    ChartType,
                    LineStyle,
                    nmfConstantsMSSPM::ShowFirstPoint,
                    nmfConstants::DontShowLegend,
                    StartForecastYear,
                    nmfConstantsMSSPM::LabelXAxisAsInts,
                    YMinVal,YMaxVal,
                    nmfConstantsMSSPM::LeaveGapsWhereNegative,
                    ChartLineSinglePlot,
                    RowLabelsForBars,
                    ColumnLabelsForLegend,
                    {HoverData[NumRunsPerForecast]},
                    MainTitle,
                    XLabel,
                    YLabel,
                    GridLines,
                    Theme,
                    LineColors[0],
                "No Uncertainty Variations",
                1.0);

        // Remove any existing MSY series
        removeMSYLines(m_ChartWidget,{"MSY = r/2","MSY = K/2"});
        removeMSYLines(m_ChartWidget,{"MSY = % of r/2","MSY = % of K/2"});

        if (isMSYBoxChecked()) {
            HoverLabels.clear();
            if (isFishingMortality) {
                HoverLabels << "MSY = r/2";
            } else if (isAbsoluteBiomass) {
                HoverLabels << "MSY = K/2";
            } else if (isRelativeBiomass) {
                HoverLabels << "";
            }
            drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                         StartForecastYear,YMinVal,YMaxVal,
                         Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                         RowLabelsForBars,ColumnLabelsForLegend,HoverLabels,
                         MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,1.0);
        }
        if (isPctMSYBoxChecked()) {
            HoverLabelsPct.clear();
            if (isFishingMortality) {
                HoverLabelsPct << "MSY = % of r/2";
            } else if (isAbsoluteBiomass) {
                HoverLabelsPct << "MSY = % of K/2";
            } else if (isRelativeBiomass) {
                HoverLabelsPct << "";
            }
            drawMSYLines(m_ChartWidget,SpeciesNum,NumSpecies,NumYearsPerRun,
                         // NumRunsPerForecast,NoUncertaintyRun,
                         StartForecastYear,YMinVal,YMaxVal,
                         Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                         RowLabelsForBars,ColumnLabelsForLegend,HoverLabelsPct,
                         MainTitle,XLabel,YLabel,nmfConstants::DontShowLegend,getPctMSYValue());
        }

        qobject_cast<QValueAxis*>(m_ChartWidget->axes(Qt::Vertical).back())->setTickCount(5);
    }
}

void
REMORA_UI::enableCarryingCapacityWidgets(bool enable)
{
    MModeKParamDL->setEnabled(enable);
    MModeKParamLE->setEnabled(enable);
    MModeKParamLB->setEnabled(enable);
    MModeKPctLB->setEnabled(enable);
}

void
REMORA_UI::enableWidgets(bool enable)
{
    MModePctMSYLE->setEnabled(enable);
    MModePctMSYDL->setEnabled(enable);
    MModeSpeciesCMB->setEnabled(enable);
    MModeSpeciesLB->setEnabled(enable);
    MModeMaxScaleFactorPB->setEnabled(enable);
    MModeShowMSYCB->setEnabled(enable);
    MModePctMSYCB->setEnabled(enable);
    MModePlotTypeSSRB->setEnabled(enable);
    MModePlotTypeMSRB->setEnabled(enable);
    MModePctMSYLBL->setEnabled(enable);
    MModeForecastPlotTypeCMB->setEnabled(enable);
    MModeForecastPlotTypeLB->setEnabled(enable);
    MModeYAxisLockCB->setEnabled(enable);
    MModeForecastTypeLB->setEnabled(enable);
    MModePlotTypeLB->setEnabled(enable);
    MModePlotScaleFactorLBL->setEnabled(enable);
    MModePlotScaleFactorCMB->setEnabled(enable);
    MModeMultiPlotTypePB->setEnabled(enable);
    if (isSingleSpecies()) {
        MModeMultiPlotTypePB->setEnabled(false);
    }
}

QString
REMORA_UI::getCarryingCapacityUncertainty()
{
    return MModeKParamLE->text();
}

QString
REMORA_UI::getForecastPlotType()
{
    return MModeForecastPlotTypeCMB->currentText();
}

QString
REMORA_UI::getGrowthUncertainty()
{
    return MModeRParamLE->text();
}

QString
REMORA_UI::getHarvestType()
{
    return MModeHarvestTypeLBL->text();
}

QString
REMORA_UI::getHarvestUncertainty()
{
    return MModeHParamLE->text();
}

bool
REMORA_UI::getLastYearsCatchValues(
        int& lastYear,
        std::vector<double>& lastYearsCatchValues)
{
    bool retv = true;
    std::vector<std::string> fields;
    std::map<std::string, std::vector<std::string> > dataMap;
    std::string queryStr;
    std::string lastYearHarvestTable = QString::fromStdString(m_HarvestType).replace("Forecast","").toStdString();
    lastYearsCatchValues.clear();

    // Get last year's catch data
    fields    = {"Value"};
    queryStr  = "SELECT Value from " + lastYearHarvestTable + " where ProjectName = '" +
                 m_ProjectName + "' AND ModelName = '" + m_ModelName + "'";
    queryStr += " AND Year = " + std::to_string(lastYear-1);

    dataMap  = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
    int NumRecords = int(dataMap["Value"].size());
    if (NumRecords > 0) {
        for (int i=0; i<NumRecords; ++i) {
            lastYearsCatchValues.push_back(std::stod(dataMap["Value"][i]));
        }
    } else {
        std::string msg = "No entries found in table: " + lastYearHarvestTable;
        m_Logger->logMsg(nmfConstants::Error,msg);
        m_Logger->logMsg(nmfConstants::Error,queryStr);
        retv = false;
    }
    return retv;
}

int
REMORA_UI::getMaxYScaleFactor(const int& speciesNum)
{
    if (speciesNum >= 0) {
        return m_MovableLineCharts[speciesNum]->getMaxYScaleFactor();
    } else {
        return MAX_SCALE_VALUE;
    }
}

int
REMORA_UI::getNumRunsPerForecast()
{
    return MModeRunsPerForecastLE->text().toInt();
}

int
REMORA_UI::getNumScaleFactorPoints(const int& speciesNum)
{
    if (speciesNum >= 0) {
        return m_MovableLineCharts[speciesNum]->getNumPoints();
    } else {
        return 2;
    }
}

int
REMORA_UI::getNumSpecies()
{
    return MModeSpeciesCMB->count();
}

std::string
REMORA_UI::getCurrentSpecies()
{
    return MModeSpeciesCMB->currentText().toStdString();
}

int
REMORA_UI::getNumYearsPerRun()
{
    return MModeYearsPerRunLE->text().toInt();
}


double
REMORA_UI::getPctMSYValue()
{
    return MModePctMSYDL->value()/100.0;
}

QList<QPointF>
REMORA_UI::getScaleFactorPoints(const int& speciesNum)
{
    if (speciesNum >= 0) {
        return m_MovableLineCharts[speciesNum]->getPoints();
    } else {
        return {};
    }
}

double
REMORA_UI::getScaleValueFromPlot(int speciesNum, int year)
{
    double scaleValue;

    if (speciesNum >= 0) {
        scaleValue = m_MovableLineCharts[speciesNum]->getYValue(year);
    } else {
        scaleValue = 1.0;
    }
    if (scaleValue < 0) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::getScaleValueFromPlot: Error reading from Scale plot");
        return 0;
    }
    return scaleValue;
}

QString
REMORA_UI::getScenarioName()
{
    return MModeScenarioNameLE->text();
}

int
REMORA_UI::getSpeciesNum()
{
    return MModeSpeciesCMB->currentIndex();
}

double
REMORA_UI::getPlotScaleFactor()
{
    std::string ScaleStr = MModePlotScaleFactorCMB->currentText().toStdString();
    double val = 1;
    if (ScaleStr == "Default") {
        val = 1.0;
    } else if (ScaleStr == "000") {
        val = 1000.0;
    } else if (ScaleStr == "000 000") {
        val = 1000000.0;
    } else if (ScaleStr == "000 000 000") {
        val = 1000000000.0;
    }

    return val;
}

QString
REMORA_UI::getYLBLPlotScaleFactor(double scaleFactor)
{
    QString scaleStr = "";
    if (scaleFactor == 1) {
        return "";
    } else if (scaleFactor == 1000) {
        scaleStr = "10^3 ";
    } else if (scaleFactor == 1000000) {
        scaleStr = "10^6 ";
    } else if (scaleFactor == 1000000000) {
        scaleStr = "10^9 ";
    }

    return scaleStr;
}

QWidget*
REMORA_UI::getTopLevelWidget()
{
    return m_TopLevelWidget;
}

void
REMORA_UI::getYearRange(int& firstYear, int& lastYear)
{
    int StartYear = 0;
    int NumYears  = 0;
    std::vector<std::string> fields;
    std::map<std::string, std::vector<std::string> > dataMap;
    std::string queryStr;

    fields   = {"StartYear","RunLength"};
    queryStr = "SELECT StartYear,RunLength from Models where ProjectName = '" + m_ProjectName +
               "' AND ModelName = '" + m_ModelName + "'";
    dataMap  = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
    if (dataMap["RunLength"].size() != 0) {
        StartYear = std::stoi(dataMap["StartYear"][0]);
        NumYears  = std::stoi(dataMap["RunLength"][0]);
        firstYear = StartYear;
        lastYear  = firstYear + NumYears;
    }
}

void
REMORA_UI::grabImage(QPixmap& pm)
{
    if (isSingleSpecies()) {
        // This will grab the Harvest Scale Factor plot as well as the Model plot(s)
        pm = MModeParentChartW->grab();
    } else {
        // This will only grab only the Model plot(s)
        if (isMultiPlot()) {
            pm = m_GridParent->grab();
        } else {
            pm = m_ChartView->grab();
        }
    }
}

bool
REMORA_UI::isAbsoluteBiomassPlotType()
{
    return (MModeForecastPlotTypeCMB->currentText() == "Biomass (absolute)");
}

bool
REMORA_UI::isDeterministic()
{
    return MModeDeterministicRB->isChecked();
}

bool
REMORA_UI::isFishingMortalityPlotType()
{
    return (MModeForecastPlotTypeCMB->currentText() == nmfConstantsMSSPM::OutputChartExploitation);
}

bool
REMORA_UI::isMultiPlot()
{
    return (MModeMultiPlotTypePB->text() == "1+");
}

bool
REMORA_UI::isMultiSpecies()
{
    return MModePlotTypeMSRB->isChecked();
}

bool
REMORA_UI::isMSYBoxChecked()
{
    return MModeShowMSYCB->isChecked();
}

bool
REMORA_UI::isPctMSYBoxChecked()
{
    return MModePctMSYCB->isChecked();
}

bool
REMORA_UI::isRelativeBiomassPlotType()
{
    return (MModeForecastPlotTypeCMB->currentText() == "Biomass (relative)");
}

bool
REMORA_UI::isSingleSpecies()
{
    return MModePlotTypeSSRB->isChecked();
}

bool
REMORA_UI::isYAxisLocked()
{
    return MModeYAxisLockCB->isChecked();
}

void
REMORA_UI::loadForecastScenario(QString filename)
{
    QString line;
    QString controlName;
    QString controlData;
    QStringList parts;
    QFile file(filename);

    m_IndexMaxYScaleFactor =  0;
    m_IndexScaleFactorChart1 =  0;
    m_IndexScaleFactorChart2 = -1;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line[0] != '#') {
               parts = line.split(":");
               controlName = parts[0].trimmed();
               controlData = parts[1].trimmed();
               // Call the setter that corresponds to the control name found in config file.
               // Using a function map so don't have to use series of if...else if... statements.
               (this->*m_FunctionMap[controlName])(controlData);
            }
        }
    }

    MModeMaxScaleFactorPB->setText(QString::number(m_MaxYAxisValues[0]));
}

QWidget*
REMORA_UI::loadUI(QWidget* parentW)
{
    QWidget* widget;
    QUiLoader loader;

    QFile file(":/forms/REMORA_UI.ui");
    file.open(QFile::ReadOnly);
    widget = loader.load(&file,parentW);
    file.close();

    return widget;
}

void
REMORA_UI::removeMSYLines(
        QChart*             chart,
        const QStringList&  MSYTypes)
{
    QList<QAbstractSeries*> allSeries = chart->series();
    int NumSeries = allSeries.size();

    for (int i=NumSeries-1; i >= 0; --i) {
        for (QString type : MSYTypes) {
            if (allSeries[i]->name().contains(type)) {
                chart->removeSeries(allSeries[i]);
                break;
            }
        }
    }
}

void
REMORA_UI::removeAllMSYLines(QString type)
{
    QStringList types;
    if (type == "%") {
        types << "MSY = % of r/2" << "MSY = % of K/2";
    } else {
        types << "MSY = r/2" << "MSY = K/2";
    }
    if (isMultiSpecies() && isMultiPlot()) {
        for (QChart* chart : m_Charts) {
            removeMSYLines(chart,types);
        }
    } else {
        removeMSYLines(m_ChartWidget,types);
    }
}

void
REMORA_UI::resetControls()
{
   setScenarioName("");
   setUncertaintyGrowth("0");
   setUncertaintyCarryingCapacity("0");
   setUncertaintyHarvest("0");
}

void
REMORA_UI::resetNumYearsOnScaleFactorCharts()
{
    for (unsigned i=0; i<m_MovableLineCharts.size(); ++i) {
        m_MovableLineCharts[i]->setRange(m_NumYearsPerRun);
    }
}

void
REMORA_UI::resetScenarioName()
{
    QString scenarioName = getScenarioName();
    scenarioName.remove('*');
    setScenarioName(scenarioName);
}

void
REMORA_UI::saveForecastParameters()
{
    int startYear;
    int endYear;
    std::string errorMsg;

    getYearRange(startYear,endYear);
    int endForecastYear = endYear + m_NumYearsPerRun;

    // Update forecast parameters in Forecasts file
    std::string cmd =
            "UPDATE Forecasts SET NumRuns = " + std::to_string(getNumRunsPerForecast()) +
            ", RunLength = " + std::to_string(getNumYearsPerRun()) +
            ", EndYear = " + std::to_string(endForecastYear) +
            ", IsDeterministic = " + std::to_string(isDeterministic()) +
            "  WHERE ProjectName = '" + m_ProjectName + "' AND ForecastName = '" + m_ForecastName + "'";
    errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
    if (nmfUtilsQt::isAnError(errorMsg)) {
        m_Logger->logMsg(nmfConstants::Error,"[Error 1] REMORA: DELETE error: " + errorMsg);
        m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
    }

    // Update seed value in main
    emit UpdateSeedValue(isDeterministic());
}

bool
REMORA_UI::saveForecastScenario(QString filename)
{
    bool retv = false;
    int numScaleFactorPoints;
    int numSpecies = getNumSpecies();
    QList<QPointF> scaleFactorPoints;
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "# "                                                  << '\n';
        stream << "# This is a REMORA Forecast configuration file"      << '\n';
        stream << "# "                                                  << '\n';
        stream << "Forecast:             " << getScenarioName()         << '\n';
        stream << "NumYearsPerRun:       " << getNumYearsPerRun()       << '\n';
        stream << "NumRunsPerForecast:   " << getNumRunsPerForecast()   << '\n';
        stream << "isDeterministic:      " << isDeterministic()         << '\n';
        stream << "isSingleSpecies:      " << isSingleSpecies()         << '\n';
        stream << "isMultiPlot:          " << isMultiPlot()             << '\n';
        stream << "ForecastDataType:     " << getForecastPlotType()     << '\n';
        stream << "isMSYLineVisible:     " << isMSYBoxChecked()         << '\n';
        stream << "r_Uncertainty:        " << getGrowthUncertainty()    << '\n';
        stream << "K_Uncertainty:        " << getCarryingCapacityUncertainty()  << '\n';
        stream << "HarvestType:          " << getHarvestType()          << '\n';
        stream << "H_Uncertainty:        " << getHarvestUncertainty()   << '\n';

        for (int speciesNum=0; speciesNum<numSpecies; ++speciesNum) {
            stream << "MaxYScaleFactor:      " << getMaxYScaleFactor(speciesNum)      << '\n';
        }

        for (int speciesNum=0; speciesNum<numSpecies; ++speciesNum) {
            // Save scale factor points from each of the per-Species scale factor plots
            numScaleFactorPoints = getNumScaleFactorPoints(speciesNum);
            stream << "NumScaleFactorPoints: " << numScaleFactorPoints << '\n';
            scaleFactorPoints = getScaleFactorPoints(speciesNum);
            for (int j=0; j<numScaleFactorPoints; ++j) {
                stream << "  point: " << scaleFactorPoints[j].x() << " " << scaleFactorPoints[j].y() << '\n';
            }
        }

        file.close();
        retv = true;
    }
    return retv;
}

bool
REMORA_UI::saveHarvestData()
{
    int NumYears = 0;
    int startYear;
    int endYear;
    int NumYearsInForecast = getNumYearsPerRun();
    std::string cmd;
    std::string errorMsg;
    double finalValue;
    std::vector<std::string> SpeNames;
    std::string Algorithm;
    std::string Minimizer;
    std::string ObjectiveCriterion;
    std::string Scaling;
    std::string CompetitionForm;
    std::vector<double> lastYearsCatchValues;

    bool modelFound = m_DatabasePtr->getAlgorithmIdentifiers(
                m_TopLevelWidget,m_Logger,m_ProjectName,m_ModelName,
                Algorithm,Minimizer,ObjectiveCriterion,Scaling,
                CompetitionForm,nmfConstantsMSSPM::DontShowPopupError);
    if (! modelFound) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::saveHarvestData: No models found");
        return false;
    }

    getYearRange(startYear,endYear);
    NumYears = endYear-startYear+1;

    m_DatabasePtr->getAllSpecies(m_Logger,SpeNames);

    cmd = "DELETE FROM " + m_HarvestType + " WHERE ProjectName = '" + m_ProjectName +
          "' AND ForecastName = '" + m_ForecastName + "'";
    errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
    if (nmfUtilsQt::isAnError(errorMsg)) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::saveHarvestData: DELETE error: " + errorMsg);
        m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
        QMessageBox::warning(m_TopLevelWidget, "Error",
                             "\nError in Save command.  Couldn't delete all records from " +
                             QString::fromStdString(m_HarvestType) + " table.\n",
                             QMessageBox::Ok);
        QApplication::restoreOverrideCursor();
        return false;
    }

    bool ok = getLastYearsCatchValues(NumYears,lastYearsCatchValues);
    if (! ok) {
        return false;
    }
    cmd = "INSERT INTO " + m_HarvestType + " (ProjectName,ForecastName,Algorithm,Minimizer,ObjectiveCriterion,Scaling,SpeName,Year,Value) VALUES ";
    for (unsigned speciesNum=0; speciesNum<SpeNames.size(); ++speciesNum) { // Species

        for (int yearNum=0; yearNum<=NumYearsInForecast; ++yearNum) { // Time
            finalValue = getScaleValueFromPlot(speciesNum,yearNum) * lastYearsCatchValues[speciesNum];

            cmd += "('" + m_ProjectName + "','" + m_ForecastName +
                    "','" + Algorithm + "','" + Minimizer +
                    "','" + ObjectiveCriterion + "','" + Scaling +
                    "','" + SpeNames[speciesNum] + "'," + std::to_string(yearNum) +
                    ", " + std::to_string(finalValue) + "),";
        }
    }

    cmd = cmd.substr(0,cmd.size()-1);

    errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
    if (nmfUtilsQt::isAnError(errorMsg)) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::saveHarvestData: Write table error: " + errorMsg);
        m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
        QApplication::restoreOverrideCursor();
        return false;
    }
    return true;
}

void
REMORA_UI::saveOutputBiomassData()
{
//std::cout << "REMORA forecastName: " << m_ForecastName << std::endl;
    emit SaveOutputBiomassData(m_ForecastName);
}

void
REMORA_UI::saveUncertaintyParameters()
{
    std::string cmd;
    std::string errorMsg;
    std::vector<std::string> SpeNames;

    for (int i = 0; i < MModeSpeciesCMB->count(); i++)
    {
        SpeNames.push_back(MModeSpeciesCMB->itemText(i).toStdString());
    }

    std::string ForecastName =  m_ForecastName;
    std::vector<std::string> fields = {"ForecastName","Algorithm","Minimizer","ObjectiveCriterion","Scaling"};
    std::string queryStr = "SELECT ForecastName,Algorithm,Minimizer,ObjectiveCriterion,Scaling FROM Forecasts where ";
    queryStr += "ProjectName = '" + m_ProjectName + "' AND ForecastName = '" + ForecastName + "'";
    std::map<std::string, std::vector<std::string> > dataMap = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);

    int NumRecords = dataMap["ForecastName"].size();
    if (NumRecords == 0) {
        std::cout << "Error: No records found." << std::endl;
        std::cout << queryStr << std::endl;
        return;
    }

    std::string Algorithm          = dataMap["Algorithm"][0];
    std::string Minimizer          = dataMap["Minimizer"][0];
    std::string ObjectiveCriterion = dataMap["ObjectiveCriterion"][0];
    std::string Scaling            = dataMap["Scaling"][0];
    std::string InitBiomass        = "0.0"; // May need to supply a dial widget for this later
    std::string GrowthRate         = std::to_string(MModeRParamLE->text().toDouble()/100.0);
    std::string CarryingCapacity   = std::to_string(MModeKParamLE->text().toDouble()/100.0);
    std::string Harvest            = std::to_string(MModeHParamLE->text().toDouble()/100.0);

    // Clear previous entry in ForecastUncertainty table
    cmd = "DELETE FROM ForecastUncertainty WHERE ProjectName = '" + m_ProjectName +
          "' AND ForecastName = '" + ForecastName + "'";
    errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
    if (nmfUtilsQt::isAnError(errorMsg)) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::callback_SavePB: DELETE error: " + errorMsg);
        m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
        QMessageBox::warning(MModeWindowWidget, "Error",
                             "\nError in Save command.  Couldn't delete all records from ForecastUncertainty table.\n",
                             QMessageBox::Ok);
        return;
    }

    QStringList ParameterNames = {"InitBiomass","GrowthRate","CarryingCapacity","Catchability",
                                  "CompetitionAlpha","CompetitionBetaSpecies","CompetitionBetaGuilds","CompetitionBetaGuildsGuilds",
                                  "PredationRho","PredationHandling","PredationExponent","SurveyQ",
                                  "Harvest"};
    cmd  = "INSERT INTO ForecastUncertainty (" ;
    cmd += "SpeName,ProjectName,ForecastName,Algorithm,Minimizer,ObjectiveCriterion,Scaling,";
    cmd +=  ParameterNames.join(",").toStdString();
    cmd += ") VALUES ";
    for (unsigned i = 0; i < SpeNames.size(); ++i) { // Species
            cmd += "('" + SpeNames[i] + "','" + m_ProjectName + "','" + ForecastName + "','" + Algorithm +
                    "','" + Minimizer + "','" + ObjectiveCriterion + "','" + Scaling + "'";
            cmd += "," + InitBiomass;
            cmd += "," + GrowthRate;
            cmd += "," + CarryingCapacity;
            // N.B. Next line will need to be modified once more parameters are used in the ForecastUncertainty calculations
            for (int i=0;i<ParameterNames.size()-4;++i) { //-4 because we are supplying data for 3 parameters + Harvest
                cmd += ", 0";
            }
            cmd += "," + Harvest + "),";

            //Ask about the number of columns in the parameter count
            //ERROR: REMORA::callback_SavePB: Write table error: Column count doesn't match value count at row 1 QMYSQL: Unable to execute query
    }
    cmd = cmd.substr(0,cmd.size()-1);

    errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
    if (nmfUtilsQt::isAnError(errorMsg)) {
        m_Logger->logMsg(nmfConstants::Error,"REMORA::callback_SavePB: Write table error: " + errorMsg);
        m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
        QMessageBox::warning(MModeWindowWidget, "Error",
                             "\nError in Save command.  Check that all cells are populated.\n",
                             QMessageBox::Ok);
        return;
    }
}

void
REMORA_UI::setAScaleFactorPoint(QString arg1)
{
    QStringList parts = arg1.split(" ");
    double xValue = parts[0].toDouble();
    double yValue = parts[1].toDouble();
    int startYear;
    int endYear;

    // Rescale x axis of plot(s)
    getYearRange(startYear,endYear);

    if ((int(xValue) == endYear) || (int(xValue) == endYear+m_NumYearsPerRun)) {
        m_MovableLineCharts[m_IndexScaleFactorChart2]->setPointYValue(m_IndexScaleFactorPoint,QPointF(xValue,yValue));
    } else {
        m_MovableLineCharts[m_IndexScaleFactorChart2]->addPoint(QPointF(xValue,yValue));
    }
    ++m_IndexScaleFactorPoint;
}

void
REMORA_UI::setDeterministic(QString isChecked)
{
   MModeDeterministicRB->setChecked(isChecked == "1");
   MModeStochasticRB->setChecked(   isChecked == "0");
}

std::string
REMORA_UI::getForecastName()
{
    return m_ForecastName;
}

void
REMORA_UI::setForecastName(QString forecastName)
{
    m_ForecastName = forecastName.toStdString();
}

void
REMORA_UI::setForecastNumRunsPerForecast(int numRunsPerForecast)
{
    m_NumRunsPerForecast = numRunsPerForecast;
    MModeRunsPerForecastSL->blockSignals(true);
    MModeRunsPerForecastLE->blockSignals(true);
    MModeRunsPerForecastSL->setValue(m_NumRunsPerForecast);
    MModeRunsPerForecastLE->setText(QString::number(numRunsPerForecast));
    MModeRunsPerForecastLE->blockSignals(false);
    MModeRunsPerForecastSL->blockSignals(false);
}

void
REMORA_UI::setForecastNumYearsPerRun(int numYearsPerRun)
{
    m_NumYearsPerRun = numYearsPerRun;
    MModeYearsPerRunLE->blockSignals(true);
    MModeYearsPerRunSL->blockSignals(true);
    MModeYearsPerRunSL->setValue(m_NumYearsPerRun);
    MModeYearsPerRunLE->setText(QString::number(numYearsPerRun));
    MModeYearsPerRunLE->blockSignals(false);
    MModeYearsPerRunSL->blockSignals(false);

    resetNumYearsOnScaleFactorCharts();
}

void
REMORA_UI::setForecastPlotType(QString arg1)
{
    MModeForecastPlotTypeCMB->setCurrentText(arg1);
}

void
REMORA_UI::setHarvestType(QString arg1)
{
    MModeHarvestTypeLBL->setText(arg1);
    m_HarvestType = "ForecastHarvest" + arg1.split(" ")[0].toStdString();
}

void
REMORA_UI::setMaxYScaleFactor(QString maxY)
{
    int value = (maxY.toInt()-1 == 0) ? MAX_SCALE_VALUE : maxY.toInt()-1;

    m_MaxYAxisValues[m_IndexMaxYScaleFactor] = maxY.toInt();
    m_MovableLineCharts[m_IndexMaxYScaleFactor]->setMaxYValue(maxY.toInt());

    ++m_IndexMaxYScaleFactor;

    MModeMaxScaleFactorPB->setText(QString::number(value));
    callback_MaxScaleFactorPB();
}

void
REMORA_UI::setMSYLineVisible(QString arg1)
{
    MModeShowMSYCB->blockSignals(true);
    MModeShowMSYCB->setChecked(arg1 == "1");
    MModeShowMSYCB->blockSignals(false);
}

void
REMORA_UI::setMultiPlot(QString isChecked)
{
    bool isMultiPlot = (isChecked == "1");

    if (isMultiPlot) {
       MModeMultiPlotTypePB->setText("1+");
    } else {
       MModeMultiPlotTypePB->setText("1");
    }
}

void
REMORA_UI::setNumRunsPerForecast(QString numRuns)
{
    MModeRunsPerForecastSL->setValue(numRuns.toInt());
    MModeRunsPerForecastLE->setText(numRuns);
}


void
REMORA_UI::setNumScaleFactorPoints(QString arg1)
{
    m_MovableLineCharts[m_IndexScaleFactorChart1++]->resetPoints();
    ++m_IndexScaleFactorChart2;
    m_IndexScaleFactorPoint = 0;
}

void
REMORA_UI::setNumYearsPerRun(QString numYearsStr)
{
    int numYears = numYearsStr.toInt();

    MModeYearsPerRunSL->setValue(numYears);
    MModeYearsPerRunLE->setText(numYearsStr);
    for (unsigned i=0; i<m_MovableLineCharts.size(); ++i) {
        m_MovableLineCharts[i]->setRange(numYears);
    }
}

void
REMORA_UI::setScenarioChanged(bool state)
{
    m_ScenarioChanged = state;
    QString scenarioName = getScenarioName();
    int last = scenarioName.size()-1;
    if (! scenarioName.isEmpty() && scenarioName[last] != "*") {
        scenarioName += "*";
        setScenarioName(scenarioName);
    }
}

void
REMORA_UI::setScenarioName(QString scenarioName)
{
    MModeScenarioNameLE->setText(scenarioName);
}

void
REMORA_UI::setSingleSpecies(QString isChecked)
{
    bool isSingleSpecies = (isChecked == "1");
    MModePlotTypeSSRB->setChecked(     isSingleSpecies);
    MModePlotTypeMSRB->setChecked(   ! isSingleSpecies);
    MModeMultiPlotTypePB->setEnabled(! isSingleSpecies);
    MModeShowMSYCB->setEnabled(isSingleSpecies || (! isSingleSpecies && isMultiPlot()));
}

void
REMORA_UI::setSpeciesList(const QStringList& speciesList)
{
    MModeSpeciesCMB->blockSignals(true);
    MModeSpeciesCMB->clear();
    MModeSpeciesCMB->addItems(speciesList);
    MModeSpeciesCMB->blockSignals(false);
}

void
REMORA_UI::InitializeScaleFactors()
{
    MModePlotScaleFactorCMB->addItem("Default");
    MModePlotScaleFactorCMB->addItem("000");
    MModePlotScaleFactorCMB->addItem("000 000");
    MModePlotScaleFactorCMB->addItem("000 000 000");
    MModePlotScaleFactorCMB->setToolTip("Sets the scale of the y-axis");
    MModePlotScaleFactorCMB->setStatusTip("Sets the scale of the y-axis");
}
void
REMORA_UI::setUncertaintyCarryingCapacity(QString arg1)
{
    MModeKParamDL->setValue(arg1.toInt());
    MModeKParamLE->setText(arg1);
}

void
REMORA_UI::setUncertaintyGrowth(QString arg1)
{
    MModeRParamDL->setValue(arg1.toInt());
    MModeRParamLE->setText(arg1);
}

void
REMORA_UI::setUncertaintyHarvest(QString arg1)
{
    MModeHParamDL->setValue(arg1.toInt());
    MModeHParamLE->setText(arg1);
}

void
REMORA_UI::setupConnections()
{
    connect(MModeYearsPerRunSL,       SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_YearsPerRunSL(int)));
    connect(MModeRunsPerForecastSL,   SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_RunsPerForecastSL(int)));
    connect(MModeRParamDL,            SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_UncertaintyRParameterDL(int)));
    connect(MModeKParamDL,            SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_UncertaintyKParameterDL(int)));
    connect(MModeHParamDL,            SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_UncertaintyHarvestParameterDL(int)));
    connect(MModeForecastRunPB,       SIGNAL(clicked()),
            this,                     SLOT(callback_RunPB()));
    connect(MModeForecastLoadPB,      SIGNAL(clicked()),
            this,                     SLOT(callback_LoadPB()));
    connect(MModeForecastSavePB,      SIGNAL(clicked()),
            this,                     SLOT(callback_SavePB()));
    connect(MModeForecastDelPB,       SIGNAL(clicked()),
            this,                     SLOT(callback_DelPB()));
    connect(MModeShowMSYCB,           SIGNAL(toggled(bool)),
            this,                     SLOT(callback_MSYCB(bool)));
    connect(MModePctMSYDL,            SIGNAL(valueChanged(int)),
            this,                     SLOT(callback_PctMSYDL(int)));
    connect(MModePctMSYCB,            SIGNAL(toggled(bool)),
            this,                     SLOT(callback_PctMSYCB(bool)));
    connect(MModeDeterministicRB,     SIGNAL(clicked(bool)),
            this,                     SLOT(callback_DeterministicRB(bool)));
    connect(MModeStochasticRB,        SIGNAL(clicked(bool)),
            this,                     SLOT(callback_StochasticRB(bool)));
    connect(MModePlotTypeSSRB,        SIGNAL(clicked(bool)),
            this,                     SLOT(callback_SingleSpeciesRB(bool)));
    connect(MModePlotTypeMSRB,        SIGNAL(clicked(bool)),
            this,                     SLOT(callback_MultiSpeciesRB(bool)));
//  connect(MModeHarvestTypePB,       SIGNAL(clicked()),
//          this,                     SLOT(callback_UncertaintyHarvestParameterPB()));
    connect(MModeSpeciesCMB,          SIGNAL(currentIndexChanged(QString)),
            this,                     SLOT(callback_SpeciesCMB(QString)));
    connect(MModeMultiPlotTypePB,     SIGNAL(clicked()),
            this,                     SLOT(callback_MultiPlotTypePB()));
    connect(MModeMaxScaleFactorPB,    SIGNAL(clicked()),
            this,                     SLOT(callback_MaxScaleFactorPB()));
    connect(MModeForecastPlotTypeCMB, SIGNAL(activated(QString)),
            this,                     SLOT(callback_ForecastPlotTypeCMB(QString)));
    connect(MModeYAxisLockCB,         SIGNAL(toggled(bool)),
            this,                     SLOT(callback_YAxisLockedCB(bool)));
    connect(MModePlotScaleFactorCMB,  SIGNAL(currentIndexChanged(QString)),
            this,                     SLOT(callback_PlotTypeScaleFactorCMB()));
}

void
REMORA_UI::setupMovableLineCharts(const QStringList& SpeciesList)
{
    int i=0;
    int startYear;
    int endYear;
    int endForecastYear;
    std::string MainTitle = "Harvest Scale Factor";
    std::string XTitle    = "Year";
    std::string YTitle    = "Scale Factor";
    std::string mainTitle;
    nmfChartMovableLine* movableLineChart;

    getYearRange(startYear,endYear);
    endForecastYear = endYear + m_NumYearsPerRun;

    MModeHarvestChartWidget->setLayout(new QVBoxLayout());
    m_MovableLineCharts.clear();
    if (SpeciesList.size() > 0) {
        for (QString Species : SpeciesList) {
            m_SpeciesMap[Species] = i++;
            mainTitle = MainTitle + ": " + Species.toStdString();
            movableLineChart = new nmfChartMovableLine(MModeHarvestChartWidget,mainTitle,XTitle,YTitle);
            movableLineChart->hide();
            movableLineChart->populateChart(endYear,endForecastYear);

            connect(this,             SIGNAL(KeyPressed(QKeyEvent*)),
                    movableLineChart, SLOT(callback_KeyPressed(QKeyEvent*)));
            connect(this,             SIGNAL(MouseMoved(QMouseEvent*)),
                    movableLineChart, SLOT(callback_MouseMoved(QMouseEvent*)));
            connect(this,             SIGNAL(MouseReleased(QMouseEvent*)),
                    movableLineChart, SLOT(callback_MouseReleased(QMouseEvent*)));

            m_MovableLineCharts.push_back(movableLineChart);

            m_MaxYAxisValues.push_back(MAX_SCALE_VALUE);
        }
        m_MovableLineCharts[0]->show();

    }
}

void
REMORA_UI::resetXAxis()
{
    int startYear;
    int endYear;
    int endForecastYear;

    // Rescale x axis of plot(s)
    getYearRange(startYear,endYear);
    endForecastYear = endYear + m_NumYearsPerRun;
    if (isMultiSpecies() && isMultiPlot()) {
        for (QChart* chart : m_Charts) {
            chart->axes(Qt::Horizontal).back()->setRange(endYear,endForecastYear);
        }
    } else {
        if (m_ChartWidget->axes().size() != 0) {
            m_ChartWidget->axes(Qt::Horizontal).back()->setRange(endYear,endForecastYear);
        }
    }
}

void
REMORA_UI::resetYAxis()
{

    if (m_MaxYAxis > 0) {
        QValueAxis* axisY = qobject_cast<QValueAxis*>(m_ChartWidget->axes(Qt::Vertical).back());

        axisY->setMax(m_MaxYAxis);

        axisY->setTickCount(5);
    }
}

void
REMORA_UI::updateYearlyScaleFactorPoints()
{
    for (int i=0; i<getNumSpecies(); ++i) {
        m_MovableLineCharts[i]->calculateYearlyPoints();
    }
}




void
REMORA_UI::callback_DelPB()
{
   QString msg;
   QString fullFilename;
   QString scenarioName = getScenarioName().remove("*");

   if (scenarioName.isEmpty()) {
       msg = "\nA scenario file must be loaded in order to delete it.\n";
       QMessageBox::information(m_TopLevelWidget, tr("Delete Scenario"), msg, QMessageBox::Ok);
       return;

   }

   msg = "\nOK to delete scenario: " + scenarioName + " ?\n\nThis cannot be undone.\n";

   QMessageBox::StandardButton reply = QMessageBox::question(
               m_TopLevelWidget,"Delete Scenario",msg,
               QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {
       fullFilename = QDir(m_RemoraScenarioDir).filePath(scenarioName);
       bool ok = QFile::remove(fullFilename);
       if (ok) {
           msg = "\nScenario file successfully deleted: " + scenarioName + "\n";
           QMessageBox::information(m_TopLevelWidget, tr("Delete Scenario"), msg, QMessageBox::Ok);
           resetControls();
       } else {
           msg = "Error: Couldn't delete scenario file: " + fullFilename;
           m_Logger->logMsg(nmfConstants::Error,msg.toStdString());
       }
   }
}

void
REMORA_UI::callback_DeterministicRB(bool pressed)
{
    MModeStochasticRB->setChecked(! pressed);
    setScenarioChanged(true);
}

void
REMORA_UI::callback_ForecastPlotTypeCMB(QString type)
{
    bool showMSYCheckboxes  = couldShowMSYCB();
    bool isBiomassAbsolute  = (type == "Biomass (absolute)");
    bool isBiomassRelative  = (type == "Biomass (relative)");
    bool isFishingMortality = (type == nmfConstantsMSSPM::OutputChartExploitation);

    MModePlotScaleFactorCMB->setEnabled(isBiomassAbsolute);
    MModePlotScaleFactorLBL->setEnabled(isBiomassAbsolute);
    if (isBiomassAbsolute) {
        MModeShowMSYCB->setEnabled(showMSYCheckboxes);
        MModePctMSYCB->setEnabled(showMSYCheckboxes);
    } else if (isBiomassRelative) {
        MModeShowMSYCB->setEnabled(false);
        MModeShowMSYCB->setChecked(false);
        MModePctMSYCB->setEnabled(false);
        MModePctMSYCB->setChecked(false);
    } else if (isFishingMortality) {
        MModeShowMSYCB->setEnabled(showMSYCheckboxes);
        MModePctMSYCB->setEnabled(showMSYCheckboxes);
    }
    drawPlot();
    setScenarioChanged(true);
}



void
REMORA_UI::callback_KeyPressed(QKeyEvent* event)
{
     emit KeyPressed(event);
}

void
REMORA_UI::callback_LoadPB()
{
    QString filename = QFileDialog::getOpenFileName(
                m_TopLevelWidget,
                tr("Load Forecast Scenario"),
                m_RemoraScenarioDir.toLatin1(),
                tr("*.scn"));
    if (! filename.isEmpty()) {
        loadForecastScenario(filename);
        callback_RunPB();
        setScenarioChanged(false);
        resetScenarioName();
    }
}

void
REMORA_UI::callback_MaxScaleFactorPB()
{
    int newValue;
    int speciesNum = getSpeciesNum();

    // Allow only values of 1, 2, 3, or 4 for the button text
    QString maxSF = MModeMaxScaleFactorPB->text();
    newValue = (maxSF.toInt()%MAX_SCALE_VALUE)+1;
    MModeMaxScaleFactorPB->setText(QString::number(newValue));
    m_MaxYAxisValues[speciesNum] = newValue;
    m_MovableLineCharts[speciesNum]->setMaxYValue(MModeMaxScaleFactorPB->text().toInt());
    setScenarioChanged(true);
}

void
REMORA_UI::callback_MouseMoved(QMouseEvent* event)
{
    emit MouseMoved(event);
}

void
REMORA_UI::callback_MouseReleased(QMouseEvent* event)
{
    emit MouseReleased(event);
}

void
REMORA_UI::callback_MSYCB(bool isChecked)
{
    if (isChecked) {
        drawMSYLines();
    } else {
        removeAllMSYLines("");
    }
    setScenarioChanged(true);
}

void
REMORA_UI::callback_MultiPlotTypePB()
{
    if (MModeMultiPlotTypePB->text() == "1") {
        MModeMultiPlotTypePB->setText("1+");
        MModeShowMSYCB->setEnabled(true);
        MModePctMSYCB->setEnabled(true);
        MModeYAxisLockCB->setEnabled(false);
    } else {
        MModeMultiPlotTypePB->setText("1");
        MModeShowMSYCB->setEnabled(false);
        MModeShowMSYCB->setChecked(false);
        MModePctMSYCB->setEnabled(false);
        MModePctMSYCB->setChecked(false);
        MModeYAxisLockCB->setEnabled(true);
    }
    drawPlot();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_MultiSpeciesRB(bool pressed)
{
    MModePlotTypeSSRB->setChecked(  ! pressed);
    MModeMultiPlotTypePB->setEnabled( pressed);
    MModeShowMSYCB->setEnabled(       pressed &&   isMultiPlot());
    MModePctMSYCB->setEnabled(        pressed &&   isMultiPlot());
    MModeYAxisLockCB->setEnabled(     pressed && ! isMultiPlot());
    if (pressed and ! isMultiPlot()) {
        MModeShowMSYCB->setChecked(false);
        MModePctMSYCB->setChecked(false);
    }
    drawPlot();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_PctMSYCB(bool isChecked)
{
    MModePctMSYDL->setEnabled(isChecked);
    MModePctMSYLE->setEnabled(isChecked);
    MModePctMSYLBL->setEnabled(isChecked);
    if (isChecked) {
        drawMSYLines();
    } else {
        removeAllMSYLines("%");
    }
    setScenarioChanged(true);
}

void
REMORA_UI::callback_PctMSYDL(int value)
{
    MModePctMSYLE->setText(QString::number(value));
    removeAllMSYLines("%");
    drawMSYLines();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_RunPB()
{
    bool ok;
    QString msg;
    QApplication::setOverrideCursor(Qt::WaitCursor);

    updateYearlyScaleFactorPoints();
    saveForecastParameters();
    saveUncertaintyParameters();
    ok = saveHarvestData();
    if (! ok) {
        QApplication::restoreOverrideCursor();
        msg = "\nREMORA run failed. Please check log for error messages.\n";
        QMessageBox::warning(m_TopLevelWidget, "Warning", msg, QMessageBox::Ok);
        return;
    }
    saveOutputBiomassData();
    drawPlot();

    enableWidgets(true);

    QApplication::restoreOverrideCursor();
}

void
REMORA_UI::callback_RunsPerForecastSL(int value)
{
    MModeRunsPerForecastLE->setText(QString::number(value));
    m_NumRunsPerForecast = value;
    setScenarioChanged(true);
}

void
REMORA_UI::callback_SavePB()
{
    QString filename = "";
    QString fullFilename = "";

    filename = QFileDialog::getSaveFileName(
                m_TopLevelWidget,
                tr("Save Forecast Scenario"),
                m_RemoraScenarioDir.toLatin1(),
                tr("*.scn"));

    if (! filename.isEmpty()) {
        // Guarantee no spaces in filenames
        filename = filename.simplified();
        filename.replace(" ","_");

        // Make sure file has a valid extension
        if (! filename.contains(".scn")) {
            fullFilename = QDir(m_RemoraScenarioDir).filePath(filename);
        } else {
            fullFilename = filename;
        }
        QFileInfo fi(fullFilename);
        QString ext = fi.suffix();
        if (ext != "scn") {
            fullFilename += ".scn";
        }

        // Update forecast qlineedit
        setScenarioName(QFileInfo(fullFilename).fileName());

        // The file fullFilename is good to save now
        bool saved = saveForecastScenario(fullFilename);
        if (saved) {
            setScenarioChanged(false);
            resetScenarioName();
        }
    }
}

void
REMORA_UI::callback_SingleSpeciesRB(bool pressed)
{
    MModePlotTypeMSRB->setChecked(   ! pressed);
    MModeYAxisLockCB->setEnabled(      pressed);
    MModeMultiPlotTypePB->setEnabled(! pressed);
    MModeShowMSYCB->setEnabled(        pressed && ! isRelativeBiomassPlotType());
    MModePctMSYCB->setEnabled(         pressed && ! isRelativeBiomassPlotType());
    drawPlot();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_SpeciesCMB(QString species)
{
    int speciesNum = getSpeciesNum();
    int numMovableLines = m_MovableLineCharts.size();

    if (numMovableLines > 0) {
        for (int i=0; i<numMovableLines; ++i) {
            m_MovableLineCharts[i]->hide();
        }
        m_MovableLineCharts[speciesNum]->show();
        MModeMaxScaleFactorPB->setText(QString::number(m_MaxYAxisValues[speciesNum]));
    }
    drawPlot();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_PlotTypeScaleFactorCMB()
{
    drawPlot();
}

void
REMORA_UI::callback_StochasticRB(bool pressed)
{
    MModeDeterministicRB->setChecked(! pressed);
    setScenarioChanged(true);
}

void
REMORA_UI::callback_UncertaintyHarvestParameterDL(int value)
{
    MModeHParamLE->setText(QString::number(value));
    setScenarioChanged(true);
}

//void
//REMORA_UI::callback_UncertaintyHarvestParameterPB()
//{
//    QString harvestType = getHarvestType();
//    if (harvestType == "Catch") {
//        MModeHarvestTypePB->setText("Effort (E)");
//        m_HarvestType = "ForecastHarvestEffort";
//    } else if (harvestType == "Effort (E)") {
//        MModeHarvestTypePB->setText("Exploitation (F)");
//        m_HarvestType = "ForecastHarvestExploitation";
//    } else if (harvestType == "Exploitation (F)") {
//        MModeHarvestTypePB->setText("Catch");
//        m_HarvestType = "ForecastHarvestCatch";
//    }
//std::cout << "m_HarvestType: " << m_HarvestType << std::endl;
//    setScenarioChanged(true);
//}

void
REMORA_UI::callback_UncertaintyKParameterDL(int value)
{
    MModeKParamLE->setText(QString::number(value));
    setScenarioChanged(true);
}

void
REMORA_UI::callback_UncertaintyRParameterDL(int value)
{
    MModeRParamLE->setText(QString::number(value));
    setScenarioChanged(true);
}

void
REMORA_UI::callback_YAxisLockedCB(bool checked)
{
    if (m_ChartWidget->axes(Qt::Vertical).back()) {
        QValueAxis* axisY = qobject_cast<QValueAxis*>(m_ChartWidget->axes(Qt::Vertical).back());
        if (checked) {
            m_MaxYAxis = axisY->max();
            axisY->setTickCount(3);
        } else {
            m_MaxYAxis = -1;
            axisY->setTickCount(5);
        }
    }
}

void
REMORA_UI::resetYearsPerRunOnScaleFactorPlot()
{
    int startYear;
    int endYear;
    int endForecastYear;
    int speciesNum = getSpeciesNum();

    // Reset year range on movable line plot
    getYearRange(startYear,endYear);
    endForecastYear = endYear + m_NumYearsPerRun;
    if (speciesNum >= 0) {
        m_MovableLineCharts[speciesNum]->updateChart(endYear,endForecastYear);
        m_MovableLineCharts[speciesNum]->resetEndPoints();
    }
    resetXAxis();
    setScenarioChanged(true);
}

void
REMORA_UI::callback_YearsPerRunSL(int value)
{
    MModeYearsPerRunLE->setText(QString::number(value));
    m_NumYearsPerRun = value;

    resetYearsPerRunOnScaleFactorPlot();
    setScenarioChanged(true);
}


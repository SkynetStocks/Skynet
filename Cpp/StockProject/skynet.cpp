#include "skynet.h"



skynet::skynet()
{
}


skynet::~skynet()
{
   if (net != nullptr)
      delete net;
   if (sS != nullptr)
      delete sS;
}

bool skynet::intitalise(const char* stock, date_time minDate, date_time maxDate, unsigned int inputs, unsigned int outputs, unsigned int hiddenLayers, unsigned int width)
{

   stockLoader sL; // creates stock loading object
   if (sL.initialise() != true)
      return false;
   sS = sL.loadStock(stock, minDate, maxDate); //loads values from stock KO stores values in a stockSampler Object
   sV = sL.loadStockVolume(stock, minDate, maxDate); //loads volumes from stock KO stores values in a stockSampler object

   nasdaqValSamp = sL.loadStock("nasdaq", minDate, maxDate);
   nasdaqVolSamp = sL.loadStockVolume("nasdaq", minDate, maxDate);

   dowjonesValSamp = sL.loadStock("dowjones", minDate, maxDate);
   dowjonesVolSamp = sL.loadStockVolume("dowjones", minDate, maxDate);

   sandpValSamp = sL.loadStock("sandp", minDate, maxDate);
   sandpVolSamp = sL.loadStockVolume("sandp", minDate, maxDate);

   cout << "stock loaded\n";
   net = new network(inputs, outputs, hiddenLayers, width, true); //create network

                                                                  //setup normalization values
   defineNormalizationValues();

   inputSections = intputDistribution(inputs);

   return true;
}
double skynet::train(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, double learningRate, const char* outputFile)
{
   vector<double> inputs, output, networkOutput, outputAnalysis, networkOutputAnalysis, diffSquared, sumError;
   double uncertaintyOfOutput, error;
   sumError.push_back(0);

   date_time subStart = start, subEnd = start; //start and end dates for the subset
   subEnd.addSeconds(subSampleLength);
   date_time outputPoint = subEnd; // output point time
   outputPoint.addSeconds(outputDistance);
   int stepsize = start.diffSeconds(end) / noItt;
   //cout << "stepsize:" << stepsize << endl;

   for (unsigned int i = 0; i < noItt; ++i)
   {
      //cout << "subStart:" << subStart.getYearI() << "," << subStart.getMonthUI() << "," << subStart.getDayUI() << "," << subStart.getHourI() << "," << subStart.getMinuteI() << "," << subStart.getSecondI() << endl;
      //cout << "subEnd:" << subEnd.getYearI() << "," << subEnd.getMonthUI() << "," << subEnd.getDayUI() << "," << subEnd.getHourI() << "," << subEnd.getMinuteI() << "," << subEnd.getSecondI() << endl;
      inputs = assembleNetworkInput(subStart, subEnd);

      double endValue = sS->getValue(subEnd, uncertaintyOfOutput);

      output.push_back(valueNormalize(sS->getValue(outputPoint, uncertaintyOfOutput) - endValue));

      net->assignInputs(inputs);
      networkOutput = net->getOutputs();
      networkOutputAnalysis.push_back(valueDenormalize(networkOutput[0]) + endValue);
      outputAnalysis.push_back(valueDenormalize(output[0]) + endValue);

      error = net->getError(output);
      diffSquared.push_back(pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2));
      sumError[0] += pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2);

      //cout << "learningRate:" << learningRateFunction(error,learningRate) << endl;
      net->train(output, learningRateFunction(error, learningRate));
      //cout << "networkOutput:" << denormalize(networkOutput[0]) << " targetOutput" << denormalize(output[0]) << endl;
      //cout << "error:" << error << endl << endl;


      inputs.clear();
      output.clear();
      subStart.addSeconds(stepsize);
      subEnd.addSeconds(stepsize);
      outputPoint.addSeconds(stepsize);
   }

   vector<vector<double>> analysisData;
   analysisData.push_back(networkOutputAnalysis);
   analysisData.push_back(outputAnalysis);
   analysisData.push_back(diffSquared);
   analysisData.push_back(sumError);
   sumError[0] = sqrt(sumError[0] / noItt);
   analysisData.push_back(sumError);
   createCSV(analysisData, outputFile);

   return sumError[0];
}

double skynet::run(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, const char* outputFile)
{
   vector<double> inputs, output, networkOutput, outputAnalysis, networkOutputAnalysis, diffSquared, sumError;
   double uncertaintyOfOutput;
   sumError.push_back(0);

   date_time subStart = start, subEnd = start; //start and end dates for the subset
   subEnd.addSeconds(subSampleLength);
   date_time outputPoint = subEnd; // output point time
   outputPoint.addSeconds(outputDistance);
   int stepsize = start.diffSeconds(end) / noItt;
   //cout << "stepsize:" << stepsize << endl;

   for (unsigned int i = 0; i < noItt; ++i)
   {
      //cout << "subStart:" << subStart.getYearI() << "," << subStart.getMonthUI() << "," << subStart.getDayUI() << "," << subStart.getHourI() << "," << subStart.getMinuteI() << "," << subStart.getSecondI() << endl;
      //cout << "subEnd:" << subEnd.getYearI() << "," << subEnd.getMonthUI() << "," << subEnd.getDayUI() << "," << subEnd.getHourI() << "," << subEnd.getMinuteI() << "," << subEnd.getSecondI() << endl;
      inputs = assembleNetworkInput(subStart, subEnd);

      double endValue = sS->getValue(subEnd, uncertaintyOfOutput);


      output.push_back(valueNormalize(sS->getValue(outputPoint, uncertaintyOfOutput) - endValue));

      net->assignInputs(inputs);
      //cout << "assigned inputs\n";
      networkOutput = net->getOutputs();
      //cout << "have outputs\n";
      networkOutputAnalysis.push_back(valueDenormalize(networkOutput[0]) + endValue);
      //cout << "push 1\n";
      outputAnalysis.push_back(valueDenormalize(output[0]) + endValue);
      //cout << "push 2\n";
      diffSquared.push_back(pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2));
      //cout << "push 3\n";
      sumError[0] += pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2);

      //cout << "networkOutput:" << denormalize(networkOutput[0]) << " targetOutput" << denormalize(output[0]) << endl;

      inputs.clear();
      output.clear();
      subStart.addSeconds(stepsize);
      subEnd.addSeconds(stepsize);
      outputPoint.addSeconds(stepsize);
   }

   vector<vector<double>> analysisData;
   analysisData.push_back(networkOutputAnalysis);
   analysisData.push_back(outputAnalysis);
   analysisData.push_back(diffSquared);
   analysisData.push_back(sumError);
   sumError[0] = sqrt(sumError[0] / noItt);
   analysisData.push_back(sumError);
   createCSV(analysisData, outputFile);

   return sumError[0];
}

vector<double> skynet::RTC(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, double learningRate)
{
   unsigned int maxRuns = 400;
   double backStepThreshold = 1, forwardStepThreshold = 0.01;
   vector<double> inputs, output, networkOutput, rmsError;
   double uncertaintyOfOutput, error;

   date_time subStart = start, subEnd = start; //start and end dates for the subset
   subEnd.addSeconds(subSampleLength);
   date_time outputPoint = subEnd; // output point time
   outputPoint.addSeconds(outputDistance);
   int stepsize = start.diffSeconds(end) / noItt;
   //cout << "stepsize:" << stepsize << endl;
   for (unsigned int runs = 0; runs < maxRuns; ++runs)
   {
      date_time subStart = start, subEnd = start; //start and end dates for the subset
      subEnd.addSeconds(subSampleLength);
      date_time outputPoint = subEnd; // output point time
      outputPoint.addSeconds(outputDistance);
      rmsError.push_back(0);
      for (unsigned int i = 0; i < noItt; ++i)
      {
         //cout << "subStart:" << subStart.getYearI() << "," << subStart.getMonthUI() << "," << subStart.getDayUI() << "," << subStart.getHourI() << "," << subStart.getMinuteI() << "," << subStart.getSecondI() << endl;
         //cout << "subEnd:" << subEnd.getYearI() << "," << subEnd.getMonthUI() << "," << subEnd.getDayUI() << "," << subEnd.getHourI() << "," << subEnd.getMinuteI() << "," << subEnd.getSecondI() << endl;

         inputs = assembleNetworkInput(subStart, subEnd);
         //cout << "getEndValue\n";
         double endValue = sS->getValue(subEnd, uncertaintyOfOutput);


         output.push_back(valueNormalize(sS->getValue(outputPoint, uncertaintyOfOutput) - endValue));
         //cout << "assignInputs\n";
         net->assignInputs(inputs);
         //cout << "getOutputs\n";
         networkOutput = net->getOutputs();
         //cout << "getError\n";
         error = net->getError(output);
         rmsError[rmsError.size() - 1] += pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2);
         //cout << "output:" << valueDenormalize(networkOutput[0]) << " target output:" << valueDenormalize(output[0]) << " diff squared:" << pow(valueDenormalize(networkOutput[0]) - valueDenormalize(output[0]), 2) << endl;

         //cout << "learningRate:" << learningRateFunction(error,learningRate) << endl;
         net->train(output, learningRateFunction(error, learningRate));
         //cout << "networkOutput:" << denormalize(networkOutput[0]) << " targetOutput" << denormalize(output[0]) << endl;
         //cout << "error:" << error << endl << endl;



         output.clear();
         subStart.addSeconds(stepsize);
         subEnd.addSeconds(stepsize);
         outputPoint.addSeconds(stepsize);
      }
      rmsError[rmsError.size() - 1] /= net->getNoInputs();
      rmsError[rmsError.size() - 1] = sqrt(rmsError[rmsError.size() - 1]);
      //cout << "rmsError:" <<  rmsError[rmsError.size() - 1] << endl;
      //check to see if converged
      if (runs != 0)
      {
         double deltaError = rmsError[rmsError.size() - 1] - rmsError[rmsError.size() - 2];
         cout << "error 1:" << rmsError[rmsError.size() - 1] << endl;
         cout << "error 2:" << rmsError[rmsError.size() - 2] << endl;
         cout << "deltaError:" << deltaError << endl;
         if (deltaError > 0)//error has increased
         {
            if (deltaError > backStepThreshold)
            {
               cout << "backstep\n";
               runs = maxRuns; //break loop
            }
         }
         else
         {
            if (abs(deltaError) < forwardStepThreshold && deltaError < 0)//insignificant change in error towards matching data set
            {
               runs = maxRuns; //break loop
               cout << "convergance\n";
            }
         }
      }
      cout << "run number:" << runs + 1 << endl << endl;
   }

   return rmsError;
}

void skynet::reset()
{
   net->resetWeights();
}

void skynet::defineNormalizationValues()
{
   double max = sS->getMaxValue();
   valueNormalizationScalar = 2 / (max*1.2); //1.2*max gives room for value to increase past the max by 20% places in range of [0,2]
   valueNormalizationOffset = -1; // to place in range of [-1,1]

   max = sV->getMaxValue();
   volumeNormalizationScalar = 2 / (max*1.2); //1.2*max gives room for value to increase past the max by 20% places in range of [0,2]
   volumeNormalizationOffset = -1; // to place in range of [-1,1]

   max = nasdaqValSamp->getMaxValue();
   nasdaqValueNormalizationScalar = 2 / (max*1.2);
   //cout << "nasdaqValueNormalizationScalar:" << nasdaqValueNormalizationScalar << endl;
   max = nasdaqVolSamp->getMaxValue();
   nasdaqVolumeNormalizationScalar = 2 / (max*1.2);
   //cout << "nasdaqVolumeNormalizationScalar:" << nasdaqVolumeNormalizationScalar << endl;

   max = dowjonesValSamp->getMaxValue();
   dowjonesValueNormalizationScalar = 2 / (max*1.2);
   //cout << "dowjonesValueNormalizationScalar:" << dowjonesValueNormalizationScalar << endl;
   max = dowjonesVolSamp->getMaxValue();
   dowjonesVolumeNormalizationScalar = 2 / (max*1.2);
   //cout << "dowjonesVolumeNormalizationScalar:" << dowjonesVolumeNormalizationScalar << endl;

   max = sandpValSamp->getMaxValue();
   sandpValueNormalizationScalar = 2 / (max*1.2);
   //cout << "sandpValueNormalizationScalar:" << sandpValueNormalizationScalar << endl;
   max = sandpVolSamp->getMaxValue();
   sandpVolumeNormalizationScalar = 2 / (max*1.2);
   //cout << "sandpVolumeNormalizationScalar:" << sandpVolumeNormalizationScalar << endl;
}

vector<double> skynet::assembleNetworkInput(date_time subStart, date_time subEnd)
{
   vector <double> inputs;
   vector<double> stockInputs, volumeInputs, nasdaqValueInputs, nasdaqVolumeInputs, dowjonesValueInputs, dowjonesVolumeInputs, sandpValueInputs, sandpVolumeInputs;

   stockSampler* valueSubSet = sS->getSubset(subStart, subEnd, inputSections[0], 1);
   stockInputs = valueSubSet->getPointsd();
   stockSampler* volumeSubSet = sV->getSubset(subStart, subEnd, inputSections[1], 1);
   volumeInputs = volumeSubSet->getPointsd();
   stockSampler* nasdaqValueSubSet = nasdaqValSamp->getSubset(subStart, subEnd, inputSections[2], 1);
   nasdaqValueInputs = nasdaqValueSubSet->getPointsd();
   stockSampler* nasdaqVolumeSubSet = nasdaqVolSamp->getSubset(subStart, subEnd, inputSections[3], 1);
   nasdaqVolumeInputs = nasdaqVolumeSubSet->getPointsd();
   stockSampler* dowjonesValueSubSet = dowjonesValSamp->getSubset(subStart, subEnd, inputSections[4], 1);
   dowjonesValueInputs = dowjonesValueSubSet->getPointsd();
   stockSampler* dowjonesVolumeSubSet = dowjonesVolSamp->getSubset(subStart, subEnd, inputSections[5], 1);
   dowjonesVolumeInputs = dowjonesVolumeSubSet->getPointsd();
   stockSampler* sandpValueSubSet = sandpValSamp->getSubset(subStart, subEnd, inputSections[6], 1);
   sandpValueInputs = sandpValueSubSet->getPointsd();
   stockSampler* sandpVolumeSubSet = sandpVolSamp->getSubset(subStart, subEnd, inputSections[7], 1);
   sandpVolumeInputs = sandpVolumeSubSet->getPointsd();

   //cout << "normalizing\n";

   for (unsigned int b = 0; b < stockInputs.size(); ++b) // normalize inputs
   {
      stockInputs[b] = valueNormalize(stockInputs[b]);
   }
   for (unsigned int b = 0; b < volumeInputs.size(); ++b) // normalize inputs
   {
      volumeInputs[b] = volumeNormalize(volumeInputs[b]);
   }
   for (unsigned int b = 0; b < nasdaqValueInputs.size(); ++b)
   {
      nasdaqValueInputs[b] = nasdaqValueNormalize(nasdaqValueInputs[b]);
   }
   for (unsigned int b = 0; b < nasdaqVolumeInputs.size(); ++b)
   {
      nasdaqVolumeInputs[b] = nasdaqVolumeNormalize(nasdaqVolumeInputs[b]);
   }
   for (unsigned int b = 0; b < dowjonesValueInputs.size(); ++b)
   {
      dowjonesValueInputs[b] = dowjonesValueNormalize(dowjonesValueInputs[b]);
   }
   for (unsigned int b = 0; b < dowjonesVolumeInputs.size(); ++b)
   {
      dowjonesVolumeInputs[b] = dowjonesVolumeNormalize(dowjonesVolumeInputs[b]);
   }
   for (unsigned int b = 0; b < sandpValueInputs.size(); ++b)
   {
      sandpValueInputs[b] = sandpValueNormalize(sandpValueInputs[b]);
   }
   for (unsigned int b = 0; b < sandpVolumeInputs.size(); ++b)
   {
      sandpVolumeInputs[b] = sandpVolumeNormalize(sandpVolumeInputs[b]);
   }

   //cout << "inserting\n";

   size_t inputSize = stockInputs.size() + volumeInputs.size() + nasdaqValueInputs.size() + nasdaqVolumeInputs.size() + dowjonesValueInputs.size() + dowjonesVolumeInputs.size() + sandpValueInputs.size() + sandpVolumeInputs.size();
   inputs.reserve(inputSize);
   inputs.insert(inputs.end(), stockInputs.begin(), stockInputs.end());
   inputs.insert(inputs.end(), volumeInputs.begin(), volumeInputs.end());
   inputs.insert(inputs.end(), nasdaqValueInputs.begin(), nasdaqValueInputs.end());
   inputs.insert(inputs.end(), nasdaqVolumeInputs.begin(), nasdaqVolumeInputs.end());
   inputs.insert(inputs.end(), dowjonesValueInputs.begin(), dowjonesValueInputs.end());
   inputs.insert(inputs.end(), dowjonesVolumeInputs.begin(), dowjonesVolumeInputs.end());
   inputs.insert(inputs.end(), sandpValueInputs.begin(), sandpValueInputs.end());
   inputs.insert(inputs.end(), sandpVolumeInputs.begin(), sandpVolumeInputs.end());

   for (unsigned int i = 0; i < inputs.size(); ++i)
   {
      //cout << inputs[i] << endl;
   }
   //cout << "inputs.size():" << inputs.size() << endl;
   //cout << "deleting\n";

   delete valueSubSet;
   delete volumeSubSet;
   delete nasdaqValueSubSet;
   delete nasdaqVolumeSubSet;
   delete dowjonesValueSubSet;
   delete dowjonesVolumeSubSet;
   delete sandpValueSubSet;
   delete sandpVolumeSubSet;

   //cout << "done deleting\n";
   return inputs;
}

double skynet::valueNormalize(double val) // normalizes a value by the normalization scalar and offset
{
   return val * valueNormalizationScalar + valueNormalizationOffset;
}

double skynet::valueDenormalize(double val) // denormalizes a value by the normalization scalar and offset
{
   return (val - valueNormalizationOffset) / valueNormalizationScalar;
}

double skynet::volumeNormalize(double val)
{
   return val * volumeNormalizationScalar + volumeNormalizationOffset;
}

double skynet::volumeDenormalize(double val)
{
   return (val - volumeNormalizationOffset) / volumeNormalizationScalar;
}

double skynet::nasdaqValueNormalize(double val)
{
   return val * nasdaqValueNormalizationScalar + nasdaqValueNormalizationOffset;
}

double skynet::nasdaqVolumeNormalize(double val)
{
   return val * nasdaqVolumeNormalizationScalar + nasdaqVolumeNormalizationOffset;
}

double skynet::dowjonesValueNormalize(double val)
{
   return val * dowjonesValueNormalizationScalar + dowjonesValueNormalizationOffset;
}

double skynet::dowjonesVolumeNormalize(double val)
{
   return val * dowjonesVolumeNormalizationScalar + dowjonesVolumeNormalizationOffset;
}

double skynet::sandpValueNormalize(double val)
{
   return val * sandpValueNormalizationScalar + sandpValueNormalizationOffset;
}

double skynet::sandpVolumeNormalize(double val)
{
   return val * sandpVolumeNormalizationScalar + sandpVolumeNormalizationOffset;
}

vector<unsigned int> skynet::intputDistribution(unsigned int noInputs)
{
   vector<double> distribution = { 0.5,0.5,0.1,0.1,0.1,0.1,0.1,0.1 };
   double totalVal = 0;
   for (unsigned int i = 0; i < distribution.size(); ++i)
   {
      totalVal += distribution[i];
   }

   vector<unsigned int> inputNumbers;
   for (unsigned int i = 0; i < distribution.size(); ++i)
   {
      inputNumbers.push_back(unsigned int(double(noInputs) * (distribution[i] / totalVal)));
   }
   unsigned int distrTotalNumbers = 0;
   for (unsigned int i = 0; i < inputNumbers.size(); ++i)
   {
      distrTotalNumbers += inputNumbers[i];
   }

   if (distrTotalNumbers > noInputs)
   {
      unsigned int numberDiff = distrTotalNumbers - noInputs;
      bool notDone = true;
      while (notDone)
      {
         for (unsigned int i = 0; (i < inputNumbers[i]) && (notDone); ++i)
         {
            --inputNumbers[i];
            --numberDiff;
            if (numberDiff <= 0)
               notDone = false;
         }
      }
   }
   else if (distrTotalNumbers < noInputs)
   {
      int numberDiff = noInputs - distrTotalNumbers;
      bool notDone = true;
      while (notDone)
      {
         for (unsigned int i = 0; (i < inputNumbers[i]) && (notDone); ++i)
         {
            ++inputNumbers[i];
            --numberDiff;
            if (numberDiff <= 0)
               notDone = false;
         }
      }

   }

   for (unsigned int i = 0; i < inputNumbers.size(); ++i)
   {
      //cout << "input number::" << i << "," << inputNumbers[i] << endl;
   }


   return inputNumbers;
}


double skynet::learningRateFunction(double totalError, double learningRate)
{
   return independant(totalError, learningRate);
}

double skynet::exponent(double error, double learningRate)
{
   return exp(error * learningRate) - 1;
}

double skynet::linear(double error, double learningRate)
{
   return error * learningRate;
}

double skynet::independant(double error, double learningRate)
{
   return learningRate;
}


//***********
string skynet::repr()
{
   ostringstream streamObj;
   streamObj << fixed;
   streamObj << setprecision(16); // CHANGE THIS TO INCREASE/DECREASE PRECISION

   streamObj << "25111723 "; // Special code. This is basically for safety. it's every other prime number until the sixth.

   streamObj << net->repr() << " ";

   streamObj << valueNormalizationScalar << " ";
   streamObj << valueNormalizationOffset << " ";
   streamObj << volumeNormalizationScalar << " ";
   streamObj << volumeNormalizationOffset << " ";

   streamObj << nasdaqValueNormalizationScalar << " ";
   streamObj << nasdaqValueNormalizationOffset << " ";
   streamObj << dowjonesValueNormalizationScalar << " ";
   streamObj << dowjonesValueNormalizationOffset << " ";
   streamObj << sandpValueNormalizationScalar << " ";
   streamObj << sandpValueNormalizationOffset << " ";

   streamObj << nasdaqVolumeNormalizationScalar << " ";
   streamObj << nasdaqVolumeNormalizationOffset << " ";
   streamObj << dowjonesVolumeNormalizationScalar << " ";
   streamObj << dowjonesVolumeNormalizationOffset << " ";
   streamObj << sandpVolumeNormalizationScalar << " ";
   streamObj << sandpVolumeNormalizationOffset << " ";

   streamObj << inputSections.size() << " ";
   for (size_t i = 0; i < inputSections.size(); i++)
   {
      streamObj << inputSections[i] << " ";
   }

   streamObj << "c";

   return streamObj.str();
}

bool skynet::eval(string repr)
{
   if (repr.size() < 8)
      return false;
   if (repr.substr(0, 8) != "25111723")
      return false;

   // Tokenizing a string
   vector<string> tokens;
   for (size_t i = 0; i < repr.size(); i++)
   {
      string token = "";
      while (repr[i] != ' ' && i < repr.size())
         token += repr[i++];
      if (token == "4072527300")
      {
         while (repr[i] != 'b')
            token += repr[i++];
         token += repr[i];
      }
      tokens.push_back(token);
   }

   size_t tokenInd = 1;

   net = &network::eval(tokens[tokenInd++]);

   valueNormalizationScalar = stringToDouble(tokens[tokenInd++]);
   valueNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   volumeNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   volumeNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   //cout << "hello";
   nasdaqValueNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   nasdaqValueNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   dowjonesValueNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   dowjonesValueNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   sandpValueNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   sandpValueNormalizationOffset = stringToDouble(tokens[tokenInd++]);

   nasdaqVolumeNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   nasdaqVolumeNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   dowjonesVolumeNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   dowjonesVolumeNormalizationOffset = stringToDouble(tokens[tokenInd++]);
   sandpVolumeNormalizationScalar = stringToDouble(tokens[tokenInd++]); 
   sandpVolumeNormalizationOffset = stringToDouble(tokens[tokenInd++]);

   size_t numSections = stringToInt(tokens[tokenInd++]);
   for (size_t i = 0; i < numSections; i++)
   {
      inputSections.push_back(stringToInt(tokens[tokenInd++]));
   }

   if (tokens[tokenInd] != "c")
      return false;

   return true;
}
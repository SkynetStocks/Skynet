#include "stockSampler.h"


stockSampler::stockSampler()
{
   pHead = new stockNode;
}


stockSampler::~stockSampler()
{
   delete pHead;//recursive delete in stockNode virtual destructor
}

void stockSampler::insert(date_time dt, double val, double un)
{
   //cout << "inserting value from date::" << dt.getYearI() << "," << dt.getMonthUI() << "," << dt.getDayUI() << "," << dt.getHourI() << "," << dt.getMinuteI() << "," << dt.getSecondI() << endl;
   stockNode* newNode = new stockNode(dt, val, un);
   stockNode* itr = pHead; //iterator
   bool done = false;
   while (done == false) //until in correctly sorted position
   {
      if (itr->getNext() == nullptr)
      {
         done = true;
         //cout << "end node\n";
      }
      else if (itr->getNext()->getDate() > dt)
      {
         done = true;
         //cout << "not end node\n";
      }
      else
         itr = itr->getNext(); //iterate
   }
   newNode->setNext(itr->getNext()); //insert into linked list
   itr->setNext(newNode);
}

bool stockSampler::remove(date_time dt)
{
   stockNode* itr = pHead;
   while (itr->getNext()->getDate() <= dt)
   {
      itr = itr->getNext();
   }
   if (itr->getNext()->getDate() == dt)
   {
      stockNode* temp = itr->getNext(); //if individual stock value exists we delete it
      itr->setNext(temp->getNext());
      delete temp;
      return true;
   }
   //if the stock point value does not exist return false to indicate it is not a node
   return false;
}

double stockSampler::getValue(date_time dt, double& uncertainty)//Linear interpolation as implementation
{
   stockNode* itr = pHead;
   bool done = false;
   while (!done)
   {
      itr = itr->getNext();
      if (itr->getNext() == nullptr)
         done = true;
      else if (itr->getNext()->getDate() > dt)
         done = true;
   }
   if (itr->getNext() == nullptr)
   {
      //cout << "case 1\n";
      int diff = dt.diffSeconds(itr->getDate()); //distance from only known point use as uncertainty
      uncertainty = diff + itr->getUncertainty();
      return itr->getValue();
   }
   else if (itr->getNext()->getDate() == dt) //if date is a stockNode return value
   {
      //cout << "case 2\n";
      uncertainty = itr->getUncertainty(); //point exists so its uncertainty is of the node that gives it
      return itr->getValue();
   }
   else if (itr->getDate().getYearI() == 0) //if before the first valid node
   {
      //cout << "case 3\n";
      int diff = dt.diffSeconds(itr->getNext()->getDate()); //distance from only known point use as uncertainty
      uncertainty = diff + itr->getNext()->getUncertainty();
      return (itr->getNext()->getValue());
   }
   else  //linearly interpolate
   {
      //cout << "case 4\n";
      int diff1 = abs(dt.diffSeconds(itr->getDate()));
      //cout << "after diff 1\n";
      int diff2 = abs(dt.diffSeconds(itr->getNext()->getDate()));
      //cout << "start ifs\n";
      if (diff1 > diff2)
      {
         uncertainty = diff2 + (itr->getUncertainty()*diff1 + itr->getNext()->getUncertainty()*diff2) / (diff1 + diff2);
      }
      else
      {
         uncertainty = diff1 + (itr->getUncertainty()*diff1 + itr->getNext()->getUncertainty()*diff2) / (diff1 + diff2);
      }
      //cout << "about to return\n";
      return (itr->getValue()*diff1 + itr->getNext()->getValue()*diff2) / (diff1 + diff2);
   }
}

double stockSampler::getMaxValue()
{
   stockNode* itr = pHead;
   bool done = false;
   double maxVal = 0;
   while (!done)
   {
      maxVal = MAX(maxVal, itr->getValue());
      itr = itr->getNext();
      if (itr->getNext() == nullptr)
         done = true;
   }
   return maxVal;
}

double stockSampler::getMinValue()
{
   stockNode* itr = pHead;
   bool done = false;
   double maxVal = 0;
   while (!done)
   {
      maxVal = MIN(maxVal, itr->getValue());
      itr = itr->getNext();
      if (itr->getNext() == nullptr)
         done = true;
   }
   return maxVal;
}

void stockSampler::clear()
{
   delete pHead->getNext(); //recusivly implemented in stockNode destructor
}

stockSampler* stockSampler::getSubset(date_time start, date_time end, unsigned int sampleNumber, double slope)
{
   //cout << "Start Subset\n";
   stockSampler* newSample = new stockSampler();
   double samplePoint;
   date_time validSamplePoint;
   date_time zeroVal(start.getDate(), T::time(0, 0, 0));
   int startSec = start.diffSeconds(zeroVal);
   int endSec = end.diffSeconds(zeroVal);

   double area = getArea(startSec, endSec, slope);
   const double areaStepSize = area / (sampleNumber - 1);

   validSamplePoint = start;

   for (int i = 0; i < sampleNumber; ++i)
   {


      double uncertainty;
      double value = getValue(validSamplePoint, uncertainty);
      newSample->insert(validSamplePoint, value, uncertainty);
      double samplePoint = validSamplePoint.diffSeconds(zeroVal);


      validSamplePoint = zeroVal;
      validSamplePoint.addSeconds(int(getNextSampleTime(samplePoint, areaStepSize, slope, startSec)));
      //cout << "current point" << double(validSamplePoint.diffSeconds(zeroVal)) / (60 * 60 * 24) << endl << endl;
   }
   //cout << "done";
   return newSample;
}

vector<stockNode> stockSampler::getPoints()
{
   vector<stockNode> values;
   bool done = false;
   if (isEmpty()) //if the stockSampler is empty return no values
   {
      //cout << "isEmpty\n";
      return values;
   }
   stockNode* itr = pHead->getNext();
   while (!done)
   {
      //cout << "next address:" << itr->getNext() << endl;
      //cout << "value:" << itr->getValue() << " uncertainty:" << itr->getUncertainty() << endl;
      values.push_back(stockNode(itr->getDate(), itr->getValue(), itr->getUncertainty()));
      if (itr->getNext() == nullptr)
         done = true;
      else
         itr = itr->getNext();
   }
   return values;
}

vector<double> stockSampler::getPointsd()
{
   vector<double> values;
   bool done = false;
   if (isEmpty()) //if the stockSampler is empty return no values
   {
      //cout << "is empty\n";
      return values;
   }
   stockNode* itr = pHead->getNext();
   while (!done)
   {
      //cout << "next address:" << itr->getNext() << endl;
      //cout << "value:" << itr->getValue() << " uncertainty:" << itr->getUncertainty() << endl;
      values.push_back(itr->getValue());
      if (itr->getNext() == nullptr)
         done = true;
      else
         itr = itr->getNext();
   }
   return values;
}



double stockSampler::getArea(double start, double end, double slope)
{
   return areaExponential(start, end, slope);
}

double stockSampler::areaExponential(double start, double end, double slope)
{
   slope /= 10;
   start /= 60 * 60 * 24;
   end /= 60 * 60 * 24;

   return (exp(slope*(end - start)) - 1) / slope;
}

double stockSampler::areaLinear(double start, double end, double slope)
{
   return (slope / 2)*(pow(end, 2) - pow(start, 2));
}

double stockSampler::areaConstant(double start, double end, double slope)
{
   return end - start;
}





double stockSampler::getNextSampleTime(double previousPoint, double subdivisionArea, double slope, double start)
{
   return nextExponentialPoint(previousPoint, subdivisionArea, slope, start);
}

double stockSampler::nextExponentialPoint(double previousPoint, double subdivisionArea, double slope, double start)
{
   slope /= 10;
   start /= 60 * 60 * 24;
   previousPoint /= 60 * 60 * 24;

   double x = slope * subdivisionArea + exp(slope*(previousPoint - start));
   x = log(x) + slope * start;
   //cout << "x:" << x << endl;
   return (x / slope) * 60 * 60 * 24;
}

double stockSampler::nextLinearPoint(double previousPoint, double subdivisionArea, double slope, double start)
{
   double x = (2 / slope) * subdivisionArea + pow(previousPoint, 2);
   //double x = (-previousPoint + sqrt(pow(previousPoint, 2) - 2 * slope*subdivisionArea)) / (2 * subdivisionArea);

   //cout << "x:" << x << endl;
   if (x < 0)
      x = 0;
   return sqrt(x);
}

double stockSampler::nextConstantPoint(double previousPoint, double subdivisionArea, double slope, double start)
{
   double x = previousPoint + subdivisionArea;
   if (x < 0)
      x = 0;
   return x;
}
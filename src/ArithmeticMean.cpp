//============================================================================
// Name        : ArithmeticMean.cpp
// Author      : Torsten Blank
// Description : A class to represent the arithmetic mean and a test program
//============================================================================

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;


class ArithmeticMean {
private:
	double m_meanValue;
	double m_numberOfValues;
public:
	// default constructor: no values, no mean value
	ArithmeticMean() : m_meanValue(0), m_numberOfValues(0) {}
	// return true, if values have been added yet
	bool isValid() const {return (m_numberOfValues > 0);}
	// add a value, return the actual mean value after adding
	void addValue(double value);
	// return the actual mean value. If no value has beend added yet, it will throw instance_invalid()
	double meanValue() const;
	// return the number of added values
	int numberOfValues() const{return m_numberOfValues;}
	// reset the class
	void reset(){m_meanValue = m_numberOfValues = 0;}

	// exception to test for valid mean value in m_meanValue
	class instance_invalid : public exception {};
};

double ArithmeticMean::meanValue() const {
	// without any value, the mean value is not defined
	if(!isValid())
		throw instance_invalid();
	return m_meanValue;
}

void ArithmeticMean::addValue(double value)
{
	if(isValid()){
		// calculate new mean value from old one including the new value
		m_meanValue = (1.0/(m_numberOfValues+1))*(value + m_numberOfValues * m_meanValue);
	}else{
		m_meanValue = value;
	}
	// new value has been added
	m_numberOfValues++;
}

int main() {
	// create instance
	ArithmeticMean am;
	// seed random engine
	srand(time(0));
	// add 500 random doubles in the range (0,100) and print mean value
	for(int i=1; i<=500; ++i){
		double rvalue = (double(rand()) / RAND_MAX)*100;
		am.addValue(rvalue);
		cout << "Added value: " << rvalue << "\t\tmean value: " << am.meanValue() << "\t\tnumber of Values: " << am.numberOfValues() << endl;
	}
	// reset mean value instance
	am.reset();
	// try to get mean value -> this should throw an exception
	try{
		double mv = am.meanValue();
		cout << "Mean value after resetting instance: " << mv << endl;
	}catch(ArithmeticMean::instance_invalid){
		cout << "Cannot get the mean value of an invalid instance of ArithmeticMean!" << endl;
	}
	return 0;
}

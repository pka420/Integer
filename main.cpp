#include <iostream>
#include <ctime>

using namespace std;

class Integer
{
private: //Private member variables
	char sign;
	int length;
	char* magnitude;

private: //Private member functions
	//These member functions are utilities useful inside the class definition ONLY.
	//We do not want them to be accessible outside the class definition.
	void appendDigit(const char &digit) {
		Integer tmp;
		if(this->length > 0) {
			tmp = *this;
			this->~Integer();
		}
		
		this->magnitude = new char[tmp.length + 1];
		this->length = tmp.length + 1;
		this->sign = tmp.sign;

		int i;
		// if tmp's length is 0, this loop would be jumped.
		for(i=0; i<tmp.length; i++) {
			this->magnitude[i] = tmp.magnitude[i];
		}
		this->magnitude[i] = digit;
	}
	void prependDigit(const char &digit) {
		Integer tmp;
		if(this->length > 0) {
			tmp = *this;
			this->~Integer();
		}
		
		this->magnitude = new char[tmp.length + 1];
		this->length = tmp.length + 1;
		this->sign = tmp.sign;
		
		this->magnitude[0] = digit;
		int i;
		// if tmp's length is 0, this loop would be jumped.
		for(i=1; i<=tmp.length; i++) {
			this->magnitude[i] = tmp.magnitude[i-1];
		}
	}
	void resize(const int &new_length) {
		if(this->length < new_length) {
			Integer tmp(*this);
			this->magnitude = new char[new_length];
			this->length = new_length;
			this->sign = tmp.sign;

			int i=0;
			while(i< (new_length-tmp.length) ) {
				this->magnitude[i] = '0';
				i++;
			}
			for(int k=0; i<new_length; i++, k++) 
				this->magnitude[i] = tmp.magnitude[k];
		}
		return;
	}
	void trim() {
		int count_zeros(0);
		//counting prevailing zeros:
		for(int i=0;i<this->length; i++) {
			if(this->magnitude[i] != '0')
				break;
			count_zeros++;
		}
		//trimming by cases:
		if(count_zeros == this->length) {
			this->~Integer();
			*this = 0;
		}
		else {
			int new_length = this->length - count_zeros;
			Integer tmp(*this);
			this->~Integer();
			this->magnitude = new char[new_length];
			for(int i=0;i<new_length;i++) {
				this->magnitude[i] = tmp.magnitude[count_zeros + i];
			}
			this->length = new_length;
			this->sign = tmp.sign;
		}
	}

	static int compare_magnitudes(const Integer &A, const Integer &B) {
		Integer tmp_A(A), tmp_B(B);

		tmp_A.trim();
		tmp_B.trim();

		if(tmp_A.length > tmp_B.length)
			return 1;
		else if(tmp_A.length < tmp_B.length)
			return 2;

		for(int i = 0 ; i < A.length ; i++) {
			if(A.magnitude[i] > B.magnitude[i])
				return 1;
			else if(A.magnitude[i] < B.magnitude[i])
				return 2;
			} 
		return 0;
	}
	static Integer add_magnitudes(const Integer &A, const Integer &B) {
		int num_a(0), num_b(0), sum(0);
		// converting:
		for(int i=0; i<A.length; i++ ) {
			num_a = num_a*10;
			num_a = num_a + (A.magnitude[i]-48);
		}
		for(int i=0; i<B.length; i++ ) {
			num_b = num_b*10;
			num_b = num_b + (B.magnitude[i]-48);
		}
		sum = num_a + num_b;
		Integer tmp_cero(sum);
		return tmp_cero;
	}
	static Integer subtract_magnitudes(const Integer &A, const Integer &B) {
		int num_a(0), num_b(0), diff(0);
		// converting:
		for(int i=0; i<A.length; i++ ) {
			num_a = num_a*10;
			num_a = num_a + (A.magnitude[i] - 48);
		}
		for(int i=0; i<B.length; i++ ) {
			num_b = num_b*10;
			num_b = num_b + (B.magnitude[i] - 48);
		}
		//subtracting:
		diff = num_a - num_b;
		Integer tmp_cero(diff);
		return tmp_cero;
	}

public: //Public member functions
	Integer();
	Integer(const int &);
	Integer(const Integer &);

	~Integer();

	Integer& operator = (const Integer &);

	Integer abs() const;

	Integer operator - () const;
	Integer& operator ++ ();
	Integer& operator -- ();
	Integer operator ++ (int);
	Integer operator -- (int);

	Integer operator + (const Integer &) const;
	Integer operator - (const Integer &) const;
	Integer operator * (const Integer &) const;
	Integer operator / (const Integer &) const;
	Integer operator % (const Integer &) const;

	Integer operator += (const Integer &);
	Integer operator -= (const Integer &);
	Integer operator *= (const Integer &);
	Integer operator /= (const Integer &);
	Integer operator %= (const Integer &);

	bool operator == (const Integer &) const;
	bool operator != (const Integer &) const;
	bool operator < (const Integer &) const;
	bool operator > (const Integer &) const;
	bool operator >= (const Integer &) const;
	bool operator <= (const Integer &) const;

	friend Integer operator + (const int &, const Integer &);
	friend Integer operator - (const int &, const Integer &);
	friend Integer operator * (const int &, const Integer &);
	friend Integer operator / (const int &, const Integer &);
	friend Integer operator % (const int &, const Integer &);

	friend bool operator == (const int &, const Integer &);
	friend bool operator != (const int &, const Integer &);
	friend bool operator > (const int &, const Integer &);
	friend bool operator < (const int &, const Integer &);
	friend bool operator >= (const int &, const Integer &);
	friend bool operator <= (const int &, const Integer &);

	friend ostream& operator << (ostream &, const Integer &);
};
/////The following function definitions are provided for you. Use them without any modification./////
Integer :: Integer()
{
	sign = '+';
	length = 0;
	//No other initialization. Do not change this function definition.
}

Integer :: Integer(const int &num) {
	if(num == 0) {
		this->length = 1;
		this->magnitude = new char[1];
		this->magnitude[0] = '0';
		this->sign = '+';
	}
	else {
		int len_num = 0;
		int n = num;
		if(n<0)
			n=-n;
		int copy2 = n;
		while(n>0) {
			n = n/10;
			len_num++;
		}
			
		this->magnitude = new char[len_num];
		int k;
		for(int i=len_num-1;i>=0;i--) {
			k = copy2%10;
			this->magnitude[i] = '0' + k;
			copy2 = copy2/10;
		}

		this->length = len_num;
		if(num < 0) 
			this->sign = '-';
		else 
			this->sign = '+';
	}
}
Integer :: Integer(const Integer & agent99) {
	if(agent99.length > 0) {
		this->magnitude = new char[agent99.length];
		for(int i=0;i<agent99.length;i++) 
			this->magnitude[i] = agent99.magnitude[i];

		this->length = agent99.length;
		this->sign = agent99.sign;
	}
}

Integer :: ~Integer() {
	if(this->length > 0) {
		this->length = 0;
		this->sign = '+';
		delete[] this->magnitude;
	}
}

Integer& Integer :: operator = (const Integer & agent99) {
	if(this->length > 0){
		this->~Integer();
	}

	if(agent99.length > 0) {
		this->magnitude = new char[agent99.length];
		for(int i=0;i<agent99.length;i++) 
			this->magnitude[i] = agent99.magnitude[i];

		this->length = agent99.length;
		this->sign = agent99.sign;
	}
	
	return *this;
}

Integer Integer :: abs() const {
	Integer tmp_cero(*this);
	tmp_cero.sign = '+';
	return tmp_cero;
}

Integer Integer :: operator - () const {
	Integer tmp_cero(*this);
	if(tmp_cero.sign == '+')
		tmp_cero.sign = '-';
	else 
		tmp_cero.sign = '+';

	return tmp_cero;
}
Integer& Integer :: operator ++ () {
	*this = *this + 1;
	return *this;
}
Integer& Integer :: operator -- () {
	*this = *this - 1;
	return *this;	
}
Integer Integer :: operator ++ (int) {
	Integer tmp_cero(*this);
	*this = *this + 1;
	return tmp_cero;
}
Integer Integer :: operator -- (int) {
	Integer tmp_cero(*this);
	*this = *this - 1;
	return tmp_cero;
}

Integer Integer :: operator + (const Integer &agent99) const {
	Integer tmp_cero(0);
	if(this->sign == agent99.sign) {
		tmp_cero = add_magnitudes(*this, agent99);
		tmp_cero.sign = this->sign;
	}
	else { 
		if( *this == agent99 )
			return tmp_cero;

		tmp_cero = subtract_magnitudes(*this, agent99);
		int compare = compare_magnitudes(*this, agent99);
		if(compare == 1) 
			tmp_cero.sign = this->sign;	
		else 
			tmp_cero.sign = agent99.sign;
	}
	return tmp_cero;
}
Integer Integer :: operator - (const Integer &agent99) const {
	Integer tmp_B(agent99);
	tmp_B = -tmp_B;
	return (*this + tmp_B);
}
Integer Integer :: operator * (const Integer &agent99) const {
 	int len1 = this->length; 
    int len2 = agent99.length; 
    int len;
    if (*this == 0 || agent99 == 0) {
    	Integer tmp_cero(0);
    	return tmp_cero; 
    }

    if(len1 > len2)
    	len = len1;
    else 
    	len = len2;

    // this is to make the lengths of both operand equal, so that A*B = B*A, no special loop conditions yo bliss.
    Integer A(*this), B(agent99);
    A.resize(len);
    B.resize(len);

    Integer result;	// this is to store result after each computation.
    int i_n1 = 0;  	// this is to keep track of zeros that are needed to be added to carry
    int i_n2 = 0; 	// this is to keep track of zero_offset. ...

    Integer carry(0);  
    Integer *store_result = new Integer[len];	// this is to store all the results and add them at the end.
    
    // Going right to left in A 
    for (int i=len-1; i>=0; i--) 
    { 
        carry = 0;
        int n1 = (A.magnitude[i]-48); 
        i_n2 = 0;  
        // Go from right to left in num2              
        for (int j=len-1; j>=0; j--) 
        { 
            int n2 = (B.magnitude[j]-48);
            int sum = n1*n2  + (carry.magnitude[0] - 48);
            // Carry for next iteration 
            carry = (sum/10); 
            //cout<<"carry after inserting is: "<<carry<<endl;
            result.prependDigit((sum%10) + '0');
            //cout<<"result after inserting is: "<<result<<endl;
            i_n2++; 
        } 
      	// adding carry and current result after ith iteration.
        if (carry > 0) {
        	for(int i=0;i<(i_n2 + i_n1);i++) 
        		carry.appendDigit(0 + '0');
            result = add_magnitudes(result, carry);
        }
        // storing current result
        store_result[i] = result;
        // preparing for next result.
        result.~Integer();
        i_n1++; 
        for(int i=0;i<i_n1;i++) {
        	result.prependDigit(0 + '0');
        }
    } 
    result = 0;
    // adding all the reusults
    for(int i=0;i<len;i++) {
    	result = add_magnitudes(store_result[i], result);
    }
 	result.trim();

 	if(this->sign == agent99.sign)
 		result.sign = '+';
 	else
 		result.sign = '-';

    return result; 
}
Integer Integer :: operator / (const Integer &agent99) const{
  	if(agent99 == 0) {	// division by 0
  		cerr<<"ERROR: Cannot divide by 0"<<endl;
  		abort();
  	}

  	Integer result(0); 
  	Integer Numerator(*this);
  	Integer Denominator(agent99);
  	Numerator.sign = '+';
  	Denominator.sign = '+';

  	if(Numerator < Denominator) 
  		return result;
  	
  	while(Numerator >= Denominator) {
  		Numerator = Numerator - Denominator;
  		result++;
  	}

  	if(this->sign != agent99.sign) 
  		result.sign = '-';
  	// else '+' -- no need to assign.
    return result;
}
Integer Integer :: operator % (const Integer &agent99) const{
	if(agent99 == 0) {
		cerr<<"ERROR: Modulo undefined on 0"<<endl;
  		abort();
  	}

  	Integer result(0); 
  	Integer Numerator(*this);
  	Integer Denominator(agent99);
  	Numerator.sign = '+';
  	Denominator.sign = '+';

  	if(Numerator < Denominator)
  		return result;

  	while(Numerator >= Denominator) {
  		Numerator = Numerator - Denominator;
  	}

  	if(this->sign != agent99.sign) 
  		Numerator.sign = '-';
  	else
  		Numerator.sign = '+';

    return Numerator;
}


Integer Integer :: operator += (const Integer &agent99) {
	*this = *this + agent99;
	return *this;
}
Integer Integer :: operator -= (const Integer &agent99) {
	*this = *this - agent99;
	return *this;
}
Integer Integer :: operator *= (const Integer &agent99) {
	*this = *this * agent99;
	return *this;
}
Integer Integer :: operator /= (const Integer &agent99) {
	*this = *this / agent99;
	return *this;
}
Integer Integer :: operator %= (const Integer &agent99) {
	*this = *this % agent99;
	return *this;
}

bool Integer :: operator == (const Integer &agent99) const{
	//cout<<"x has sign"<<this->sign<<endl;
	//	cout<<"d1 has sign"<<agent99.sign<<endl;
	if(this->sign == agent99.sign)
		if(compare_magnitudes(*this, agent99) == 0)
			return true;

	return false;
}
bool Integer :: operator != (const Integer &agent99) const{
	return !(*this == agent99);
}

bool Integer :: operator > (const Integer &agent99) const {
	if(this->sign != agent99.sign ) {
		if(this->sign == '+') 
			return true;
		else 
			return false;
	}
	else {
			int compare = compare_magnitudes(*this, agent99);
			if(this->sign == '+') 
				if(compare == 1)
					return true;
				else 
					return false;
			else
				if(compare == 1)
					return false;
				else
					return true;
		}
	return false;
}
bool Integer :: operator < (const Integer &agent99) const{
	return !(*this > agent99);
}
bool Integer :: operator >= (const Integer &agent99) const{
	if(*this == agent99)
		return true;
	else if(*this > agent99)
		return true;

	return false;
}
bool Integer :: operator <= (const Integer &agent99) const{
	if(*this == agent99)
		return true;
	else if(*this < agent99)
		return true;

	return false;
}

Integer operator + (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero + agent99);
}
Integer operator - (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero - agent99);
}
Integer operator * (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero * agent99);
}
Integer operator / (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero / agent99);
}
Integer operator % (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero % agent99);
}

bool operator == (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return tmp_cero == agent99;
}
bool operator != (const int &una, const Integer &agent99) {
	return !( una == agent99);
}
bool operator > (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero > agent99);
}
bool operator < (const int &una, const Integer &agent99) {
	return !(una > agent99);
}
bool operator >= (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero >= agent99);
}
bool operator <= (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return (tmp_cero <= agent99);
}

ostream& operator << (ostream &out, const Integer &d)
{
	if (d.length == 0)
		out << "Not Initialized";
	else
	{
		if (d.sign == '-')
			out << '-';
		for (int i = 0; i < d.length; i++)
			out << d.magnitude[i];
	}
	return out;
}














/*
int main() {
	Integer a(65);
	Integer b(2);
	cout<<"noice is: "<< (a%b) <<endl;

	a = -68;
	b = -9;
	cout<<"noice is: "<< (a%b) <<endl;

	a = 70;
	b = -1;
	cout<<"noice is: "<< (a%b) <<endl;

	a = -7058;
	b = 3;
	cout<<"noice is: "<< (a%b) <<endl;
}
*/




////////////End of provided function definitions. Use them without any modification.///////////////
int main()
{
	//Test constructors
	Integer n1, n2(-10023);
	Integer n3(n2);
	cout << "Default Integer object n1 is " << n1 << endl;
	cout << "Non-default Integer object n2 is " << n2 << endl;
	cout << "Non-default Integer object n3 is " << n3 << endl;

	//Test destructor
	n2.~Integer();
	cout << "After destructing it, n2 is now " << n2 << endl;

	//Test assignment operators
	n1 = n3;
	cout << "After assigning n1 the value of n3, n1 is now " << n1 << endl;
	n2 = 8;
	cout << "After assigning n2 the integer value 8, n2 is now " << n2 << endl;

	//Test absolute value
	cout << "The absolute value of n1 is " << n1.abs() << endl;
	cout << "The absolute value of n2 is " << n2.abs() << endl;
	cout << "The absolute value of n3 is " << n3.abs() << endl;

	//Test arithmetic operations with relatively small values in order to validate the correctness of our program
	int x, y, z;
	Integer d1, d2, d3, d4;
	bool success = true;
	srand(time(0)); //Comment this line of code to get same random numbers on repeated runs of the program
	for (int i = 0; i < 25; i++) //You may loop more iterations to test thoroughly
	{
		cout << "========================================================" << endl;
		//Test equality comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x == y ? cout << x << " == " << y << endl : cout << x << " is not ==  " << y << endl;
		d1 == d2 ? cout << d1 << " == " << d2 << endl : cout << d1 << " is not == " << d2 << endl;
		x == d2 ? cout << x << " == " << d2 << endl : cout << x << " is not == " << d2 << endl;
		if (((x == y) == (d1 == d2)) && ((x == y) == (x == d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test not equality comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x != y ? cout << x << " != " << y << endl : cout << x << " is not != " << y << endl;
		d1 != d2 ? cout << d1 << " != " << d2 << endl : cout << d1 << " is not != " << d2 << endl;
		x != d2 ? cout << x << " != " << d2 << endl : cout << x << " is not != " << d2 << endl;
		if (((x != y) == (d1 != d2)) && ((x != y) == (x != d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test greater than comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x > y ? cout << x << " > " << y << endl : cout << x << " is not > " << y << endl;
		d1 > d2 ? cout << d1 << " > " << d2 << endl : cout << d1 << " is not > " << d2 << endl;
		x > d2 ? cout << x << " > " << d2 << endl : cout << x << " is not > " << d2 << endl;
		if (((x > y) == (d1 > d2)) && ((x > y) == (x > d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test less than comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x < y ? cout << x << " < " << y << endl : cout << x << " is not < " << y << endl;
		d1 < d2 ? cout << d1 << " < " << d2 << endl : cout << d1 << " is not < " << d2 << endl;
		x < d2 ? cout << x << " < " << d2 << endl : cout << x << " is not < " << d2 << endl;
		if (((x < y) == (d1 < d2)) && ((x < y) == (x < d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test greater than or equal comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x >= y ? cout << x << " >= " << y << endl : cout << x << " is not >= " << y << endl;
		d1 >= d2 ? cout << d1 << " >= " << d2 << endl : cout << d1 << " is not >= " << d2 << endl;
		x >= d2 ? cout << x << " >= " << d2 << endl : cout << x << " is not >= " << d2 << endl;
		if (((x >= y) == (d1 >= d2)) && ((x >= y) == (x >= d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test less than or equal comparison
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		x <= y ? cout << x << " <= " << y << endl : cout << x << " is not <= " << y << endl;
		d1 <= d2 ? cout << d1 << " <= " << d2 << endl : cout << d1 << " is not <= " << d2 << endl;
		x <= d2 ? cout << x << " <= " << d2 << endl : cout << x << " is not <= " << d2 << endl;
		if (((x <= y) == (d1 <= d2)) && ((x <= y) == (x <= d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test arithmetic negation operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and -x is " << -x << endl;
		cout << "d1 = " << d1 << " and -d1 is " << -d1 << endl;
		if (-d1 == -x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test pre-increment operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		cout << "++x is " << ++x << endl;
		cout << "d1 = " << d1 << " and ";
		cout << "++d1 is " << ++d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test pre-decrement operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		cout << "--x is " << --x << endl;
		cout << "d1 = " << d1 << " and ";
		cout << "--d1 is " << --d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test post-increment operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		x++;
		cout << "x++ is " << x << endl;
		cout << "d1 = " << d1 << " and ";
		d1++;
		cout << "d1++ is " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test post-decrement operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		x--;
		cout << "x-- is " << x << endl;
		cout << "d1 = " << d1 << " and ";
		d1--;
		cout << "d1-- is " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test addition operation
		x = rand()%2 ? rand() : -rand();
		//x = -10;
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		//y = -10;
		d2 = y;
		z = x + y;
		d3 = d1 + d2;
		d4 = x + d2;
		cout << x << " + " << y << " = " << z << endl;
		cout << d1 << " + " << d2 << " = " << d3 << endl;
		cout << x << " + " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test subtraction operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		z = x - y;
		d3 = d1 - d2;
		d4 = x - d2;
		cout << x << " - " << y << " = " << z << endl;
		cout << d1 << " - " << d2 << " = " << d3 << endl;
		cout << x << " - " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test multiplication operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		z = x * y;
		d3 = d1 * d2;
		d4 = x * d2;
		cout << x << " * " << y << " = " << z << endl;
		cout << d1 << " * " << d2 << " = " << d3 << endl;
		cout << x << " * " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test division operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		z = x / y;
		d3 = d1 / d2;
		d4 = x / d2;
		cout << x << " / " << y << " = " << z << endl;
		cout << d1 << " / " << d2 << " = " << d3 << endl;
		cout << x << " / " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test modulo operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		z = x % y;
		d3 = d1 % d2;
		d4 = x % d2;
		cout << x << " % " << y << " = " << z << endl;
		cout << d1 << " % " << d2 << " = " << d3 << endl;
		cout << x << " % " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound addition operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x += y;
		cout << "x += y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 += d2;
		cout << "d1 += d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound subtraction operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x -= y;
		cout << "x -= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 -= d2;
		cout << "d1 -= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound multiplication operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x *= y;
		cout << "x *= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 *= d2;
		cout << "d1 *= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound division operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x /= y;
		cout << "x /= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 /= d2;
		cout << "d1 /= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound modulo operation
		x = rand()%2 ? rand() : -rand();
		d1 = x;
		y = rand()%2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x %= y;
		cout << "x %= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 %= d2;
		cout << "d1 %= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << "========================================================" << endl;
		cout << endl << endl;

		//system("Pause"); //You may comment this line of code depending on your desire to pause after every iteration
	}

	if (success)
		cout << endl << "Looks like all your computations were correct. Congratulations!" << endl;

	system("Pause");
	return 0;
}


/*

int main()
{
	
	Integer d1 = 1, d2 = 1, d3;
	srand(time(0));
	char ch;
	do
	{
		d1 *= rand();
		d2 *= rand();
		d3 = d1 * d2;
		cout << "First Number = " << d1 << endl;
		cout << "Second Number = " << d2 << endl;
		cout << "Their Product = " << d3 << endl << endl;
		cout << "Do you want to keep on multiplying? (y/n): ";
		cin >> ch;
	}while ((ch == 'y') || (ch == 'Y'));

	system("Pause");
	return 0;
}
*/

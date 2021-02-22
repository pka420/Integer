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
		Integer tmp(*this);
		if(this->length > 0)
			this->~Integer();

		this->magnitude = new char[tmp.length + 1];
		this->length = tmp.length + 1;
		this->sign = tmp.sign;

		int i;
		for(i=0; i<tmp.length; i++) {
			this->magnitude[i] = tmp.magnitude[i];
		}
		this->magnitude[i] = digit;
	}
	void prependDigit(const char &digit) {
		Integer tmp(*this);
		if(this->length > 0)
			this->~Integer();

		this->magnitude = new char[tmp.length + 1];
		this->length = tmp.length + 1;
		this->sign = tmp.sign;

		this->magnitude[0] = digit;
		for(int i=1; i<tmp.length; i++) {
			this->magnitude[i] = tmp.magnitude[i];
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
				this->magnitude[i] = static_cast<char>(0);
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
		if(A.length > B.length)
			return 1;
		else if(A.length < B.length)
			return 2;
		else {
			for(int i = 0 ; i < A.length ; i++) {
				if(A.magnitude[i] > B.magnitude[i])
					return 1;
				else 
					return 2;
			}
		return 0;
		} 

	}
	static Integer add_magnitudes(const Integer &A, const Integer &B) {
		int num_a(0), num_b(0), sum(0);
		// converting:
		for(int i=0; i<A.length; i++ ) {
			num_a = num_a*10;
			num_a = num_a + static_cast<int>(A.magnitude[i]);
		}
		for(int i=0; i<B.length; i++ ) {
			num_b = num_b*10;
			num_b = num_b + static_cast<int>(B.magnitude[i]);
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
			num_a = num_a + static_cast<int>(A.magnitude[i]);
		}
		for(int i=0; i<B.length; i++ ) {
			num_b = num_b*10;
			num_b = num_b + static_cast<int>(B.magnitude[i]);
		}
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
		cout<<static_cast<char>(k);
		this->magnitude[i] = k;
		copy2 = copy2/10;
	}

	this->length = len_num;
	if(num < 0) 
		this->sign = '-';
	else 
		this->sign = '+';
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
Integer& Integer :: operator -- (){
	*this = *this - 1;
	return *this;	
}
Integer Integer :: operator ++ (int){
	Integer tmp_cero(*this);
	*this = *this+1;
	return tmp_cero;
}
Integer Integer :: operator -- (int){
	Integer tmp_cero(*this);
	*this = *this-1;
	return tmp_cero;
}

Integer Integer :: operator + (const Integer &agent99) const {
	Integer tmp_cero;
	if(this->sign == agent99.sign) {
		tmp_cero = add_magnitudes(*this, agent99);
		tmp_cero.sign = this->sign;
	}
	else { 
		int real_int = compare_magnitudes(*this, agent99);
		if( real_int == 0) {
			tmp_cero = 0;
			return tmp_cero;
		}
		else if( real_int == 1)
			tmp_cero.sign = this->sign;
		else 
			tmp_cero.sign = agent99.sign;
		
		Integer tmp_cero = subtract_magnitudes(*this, agent99);
	}
	return tmp_cero;
}
Integer Integer :: operator - (const Integer &agent99) const{
	Integer tmp_B(agent99);
	tmp_B = - tmp_B;
	return (*this + agent99);
}
Integer Integer :: operator * (const Integer &agent99) const{
	int a(0), b(0);
	// converting to integers:
	for(int i=0;i<this->length;i++) {
		a = a*10;
		a = a + static_cast<int>(this->magnitude[i]);
	}
	for(int i=0;i<agent99.length;i++) {
		b = b*10;
		b = b + static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	b = -b;
	if(this->sign == '-')
    	a = -a;

    Integer tmp_cero(a*b);
    return tmp_cero;
}
Integer Integer :: operator / (const Integer &agent99) const{
	int a(0), b(0);
	// converting to integers:
	for(int i=0;i<this->length;i++) {
		a = a*10;
		a = a + static_cast<int>(this->magnitude[i]);
	}
	for(int i=0;i<agent99.length;i++) {
		b = b*10;
		b = b + static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	b = -b;
	if(this->sign == '-')
    	a = -a;

    Integer tmp_cero(a/b);
    return tmp_cero;
}
Integer Integer :: operator % (const Integer &agent99) const{
	int a(0), b(0);
	// converting to integers:
	for(int i=0;i<this->length;i++) {
		a = a*10;
		a = a + static_cast<int>(this->magnitude[i]);
	}
	for(int i=0;i<agent99.length;i++) {
		b = b*10;
		b = b + static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	b = -b;
	if(this->sign == '-')
    	a = -a;

    Integer tmp_cero(a%b);
    return tmp_cero;
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
	if(this->sign == agent99.sign)
		if(compare_magnitudes(*this, agent99) == 0)
			return true;
	return false;
}
bool Integer :: operator != (const Integer &agent99) const{
	return !(*this == agent99);
}

bool Integer :: operator > (const Integer &agent99) const {
	if(this->sign == '+' && agent99.sign == '-') 
		return true;
	else if(this->sign == '-' && agent99.sign == '+')
		return false;
	else {
		if(this->length > agent99.length)
			return true;
		else if(this->length < agent99.length)
			return false;
		else {
			if(compare_magnitudes(*this, agent99) == 1)
				return true;
		}
	}
	return false;
}
bool Integer :: operator < (const Integer &agent99) const{
	return !(this->operator>(agent99));
}
bool Integer :: operator >= (const Integer &agent99) const{
	if(this->sign == '+' && agent99.sign == '-') 
		return true;
	else if(this->sign == '-' && agent99.sign == '+')
		return false;
	else {
		if(this->length > agent99.length)
			return true;
		else if(this->length < agent99.length)
			return false;
		else {
			if(compare_magnitudes(*this, agent99) != -1 )
				return true;
		}
	}
	return false;	
}
bool Integer :: operator <= (const Integer &agent99) const{
	if(this->sign == '+' && agent99.sign == '-') 
		return true;
	else if(this->sign == '-' && agent99.sign == '+')
		return false;
	else {
		if(this->length > agent99.length)
			return true;
		else if(this->length < agent99.length)
			return false;
		else {
			if(compare_magnitudes(*this, agent99) != 1 )
				return true;
		}
	}
	return false;
}

Integer operator + (const int &una, const Integer &agent99) {
	int num(0);
	//converting:
	for(int i=0;i<agent99.length;i++) {
		num = num*10;
		num = static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	num = -num;

    Integer tmp_cero(una + num);
	return tmp_cero;
}
Integer operator - (const int &una, const Integer &agent99) {
	int num(0);
	//converting:
	for(int i=0;i<agent99.length;i++) {
		num = num*10;
		num = static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	num = -num;

    Integer tmp_cero(una - num);
	return tmp_cero;
}
Integer operator * (const int &una, const Integer &agent99) {
	int num(0);
	//converting:
	for(int i=0;i<agent99.length;i++) {
		num = num*10;
		num = static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	num = -num;

    Integer tmp_cero(una * num);
	return tmp_cero;
}
Integer operator / (const int &una, const Integer &agent99) {
	int num(0);
	//converting:
	for(int i=0;i<agent99.length;i++) {
		num = num*10;
		num = static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	num = -num;

    Integer tmp_cero(una / num);
	return tmp_cero;
}
Integer operator % (const int &una, const Integer &agent99) {
	int num(0);
	//converting:
	for(int i=0;i<agent99.length;i++) {
		num = num*10;
		num = static_cast<int>(agent99.magnitude[i]);
	}
    // signing:
    if(agent99.sign == '-')
    	num = -num;

    Integer tmp_cero(una % num);
	return tmp_cero;
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
	return tmp_cero > agent99;
}
bool operator < (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return !(tmp_cero > agent99);
}
bool operator >= (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return tmp_cero <= agent99;
}
bool operator <= (const int &una, const Integer &agent99) {
	Integer tmp_cero(una);
	return tmp_cero <= agent99;
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






































////////////End of provided function definitions. Use them without any modification.///////////////
int main()
{
	//Test constructors
	Integer n1, n2(-10023);
	//Integer n3(n2);
	Integer n3;
	cout << "Default Integer object n1 is " << n1 << endl;
	cout << "Non-default Integer object n2 is " << n2 << endl;
	cout << "Non-default Integer object n3 is " << n3 << endl;
/*
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
		d1 = x;
		y = rand()%2 ? rand() : -rand();
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
*/
	system("Pause");
	return 0;
}


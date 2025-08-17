class TestStruct {
	int a;
	void print() {
		this.print(getA());
	}
	void print(int value) {
		Print(value);
	}
	int getA() {
		return a;
	}
}

int myInt;
int Main() {
	int myInt = 45;
	float myFloat = myInt;

	TestStruct test = { myInt };
	test.print();

	return 0;
}
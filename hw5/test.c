int foo(float a[][3])
{
	write(a[0][1]);
}
int MAIN()
{
	float A[5][3];
	A[0][1] = 1.2;
	foo(A);
}

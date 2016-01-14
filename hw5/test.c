int MAIN()
{
	float A[10][20];
	float a, b;
	int x, y;
	x = 1;
	y = 2;
	A[x][y] = 1.0;
	A[2][3] = 2.0;
	a = A[x][y];
	b = A[2][3];
	write(a);
	write("\n");
	write(b);
	write("\n");
}

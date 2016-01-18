int MAIN()
{
	int i;
	int j = 0;
	for(i=0; i<10 && j<5; i = i + 1)
	{
		write(i);
		write("\n");
		j=j+1;
	}
}

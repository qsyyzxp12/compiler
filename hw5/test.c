int foo()
{
	write("xxx\n");
	return 0;
}

int MAIN()
{
	if(0 || foo())
	{
		write("1");
	}
	else
	{
		write("2");
	}
}

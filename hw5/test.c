int foo()
{
	write("xxx\n");
	return 0;
}

int MAIN()
{
	if(1 && foo())
	{
		write("1\n");
	}
}

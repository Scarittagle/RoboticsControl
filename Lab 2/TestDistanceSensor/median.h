//show median of an array

float findMedian(float array[], int n)
{
    //Copying the array
    float sortedArr[sizeof(array)];
    for(int i = 0; i < sizeof(array); i++){
        sortedArr[i] = array[i];
    }
    //sorting Process
    float tmp;
    for(int i = 0;i < sizeof(sortedArr);i++)
	{
		for (int j = i + 1;j < 10;j++)
		{
			if (sortedArr[i] > sortedArr[j])
			{
				tmp  = sortedArr[i];
				sortedArr[i] = sortedArr[j];
				sortedArr[j] = tmp;
			}
		}
    }

    //find median
    float med =0;
    int a=0;
    int b=0;
    float newMed=0;
    if (n % 2 ==0){
        a=n/2;
        b=(n/2)-1;
        med = (sortedArr[a] + sortedArr[b]);
        newMed = (med/2);
    }


    return newMed;
 }

// int a[] = { 1, 3, 4, 2, 7, 5, 8, 6 };
//int n = sizeof(a)/sizeof(a[0]);
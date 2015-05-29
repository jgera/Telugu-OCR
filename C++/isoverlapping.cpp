int isoverlapping(stroke1,stroke2)
{
	minx1=min(stroke1.points(:,1));
	maxx1=max(stroke1.points(:,1));
	minx2=min(stroke2.points(:,1));
	maxx2=max(stroke2.points(:,1));
	if(minx1<minx2)
    {
    	a=maxx1-minx2;
        b=maxx1-minx1;
        c=a/b;
    }    
        
	else
    {
    	a=maxx2-minx1;
        b=maxx2-minx2;
        c=a/b;
    }   	
        
	if c>0        
    	y=1;
	else
    	y=0;

    return y
}


    
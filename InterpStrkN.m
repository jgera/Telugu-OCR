function strko = InterpStrkN(strk, n)
%INTERPSTRK() interpolates a stroke by reducing the stepsize by
%a factor of 'n'.


	strko = strk;
    tmpx = interpolate1(strk.points(:,1), n);
	
    tmpy = interpolate1(strk.points(:,2), n);
    z = [tmpx' tmpy'];
	strko.points = z;




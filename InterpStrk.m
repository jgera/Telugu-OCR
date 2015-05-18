function strko = InterpStrk(strk, n)
%INTERPSTRK() interpolates a stroke by reducing the stepsize by
%a factor of 'n'.

if(strk.basetype == 0)
	strko = strk;
    tmpx = interpolate1(strk.points(:,1), n);
	
    tmpy = interpolate1(strk.points(:,2), n);
    z = [tmpx' tmpy'];
	strko.points = z;
else
   fprintf('ERROR in InterpStrk(). Cannot interpolate a stroke\n');
   fprintf('with a base.\n');
   
end




function ret=IsCusp3(x,  y)

% int hw2, retvalue;
% 	float *tmpx, *tmpy;
% 	float ml, mr, cl, cr;
% 	double thetal, thetar, dif;
% 	double pi = 3.141592654;

arr_size = length(x);

tmp=mod(arr_size,2);

	if(tmp==1)
		hw2 = (arr_size-1)/2;
	else
		hw2 = (arr_size)/2;
    end

	
%//	LineFit(x, y, 

vec1 = [x(hw2)-x(1), y(hw2)-y(1)];
vec1 = vec1/norm(vec1);

vec2 = [x(arr_size)-x(hw2), y(arr_size)-y(hw2)];
vec2 = vec2/norm(vec2);

dif = norm(vec1 - vec2);


%keyboard




CUSP_THRESH=1.7;
	if(dif > CUSP_THRESH)
		ret =  1;
	else
		ret = 0;
    end
    
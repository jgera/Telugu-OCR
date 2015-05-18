function yo = interpolate1(y, n)
%INTERPOLATE() interpolates an array (assuming uniform samples)

len = length(y);

x=[1:len];
step = 1/n;        
xi = [1:step:len];
yo = interp1(x, y, xi, 'spline');
function strksm = SmoothStrk(strk)
%SMOOTHSTRK() smooths a stroke by convolving with a gaussian.

x = smootharray(strk.points(:,1));
y = smootharray(strk.points(:,2));

 strksm = strk;

c = [x, y];

strksm.points = c;
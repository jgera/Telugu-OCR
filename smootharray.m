function y = smootharray(x)
%[x,y]=size(x);  

xlen = length(x);
%win = 15;


win = floor(xlen/5);

if(win < 1)
    win = 1;
end
if(mod(win,2) == 0)
    win = win + 1;
end
win;

if(xlen < win)
    y=x;
    return;
end

win2 = (win-1)/2;
sigma = win2;

for i=1:win,
gau(i)=(1/(sqrt(2*pi)*sigma))*exp(-(((i-win2)*(i-win2))/(2*sigma*sigma)));
end
  
  gau = gau/sum(gau);    % gaussian
  

  
prepad = x(1)*ones(win2,1);
postpad = x(xlen)*ones(win2,1);
xmod = [prepad; x; postpad];
y =conv(xmod,gau);

len = length(y);

y(len-win+2:len)=[];
y(1:win-1)=[];

plotting = 0;
if(plotting)
plot(x)
hold on
plot(y,'g')
hold off
%while returning initial and final points have to be removed

end

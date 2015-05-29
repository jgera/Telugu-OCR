function y=determinefeatures(strokearray)
bauxpoints=strokearray.points;
s1=floor(length(bauxpoints));
start=floor(0.09*length(bauxpoints));
slope=[];
y1=0;
y2=0;
bauxpoints = bauxpoints(start:s1,:);
temp = bauxpoints(1,:);
bauxpoints(1,:)=bauxpoints(1,:)-temp;
%bauxpoints(start,:):bauxpoints(s1,:)
index=0;
for i=2:length(bauxpoints)
    bauxpoints(i,:)=bauxpoints(i,:)-temp;
    if (bauxpoints(i,2)>=0)
        index=i-1;
        break
    end
end
%bauxpoints

for i=1:index-1
    
    if bauxpoints(i,1)<0 && bauxpoints(i,2)<=0
        %if abs(bauxpoints(i,1))>=abs(2*bauxpoints(i,2))   % negative so comparing sign will be opposite
            y1=1;
    else
            y1=0;
    %    end
    end
    if bauxpoints(i,1)>=0 && bauxpoints(i,2)<=0                          %this complete part includes that points should lie with the specified range.(we have taken 225 to 330 degree range)
    %    if abs(bauxpoints(i,1))<=abs(2*abs(bauxpoints(i,2)));
            y1=1;
    else
            y1=0;
    %    end
    end
        
    
    slope(i)=(bauxpoints(i+1,2)-bauxpoints(i,2))/(bauxpoints(i+1,1)-bauxpoints(i,1));
end

indices_of_neg = find(slope<0);
indices_of_pos = find(slope>0);

if mean(indices_of_neg) < mean(indices_of_pos)
        y2=1;
else
        y2=0;
end

if y1==1 && y2==1
    y=1;
else
    y=0;
end


function y=isoverlapping(stroke1,stroke2)
assert(isa(stroke1,'double'));
assert(isa(stroke2,'double'));
minx1=min(stroke1(:,1));
maxx1=max(stroke1(:,1));
minx2=min(stroke2(:,1));
maxx2=max(stroke2(:,1));
if(minx1<minx2)
    
        a=maxx1-minx2;
        b=maxx1-minx1;
        c=a/b;
        
else
    
        a=maxx2-minx1;
        b=maxx2-minx2;
        c=a/b;
        
end
if c>0        %there should be atleast 20%overlap--threshold
    y=1;
else
    y=0;
end
end

    
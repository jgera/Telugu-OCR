function y=isbelow(stroke1,stroke2)

if isoverlapping(stroke1,stroke2)
        if max(stroke1.points(:,2))<(0.2*range(stroke2.points(:,2))+min(stroke2.points(:,2)))
            y=1;
        else
            y=0;
        end
    
else
    y=0;
end

            
            
        




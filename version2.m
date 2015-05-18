
load('complete_wrong_data_730')
q=1;
colorc=1;
colors=['r','g','b','y','m'];
% y=[];
nstrokearray=[];
v=1;
uncl=0;
for v=1:20
    nstrokearray = [];
    m=1;
    for j=1:X(v).nchars
        for k=1:X(v).chararr(j).nsgs%Loop over each sgarray in the character
            for l=1:X(v).chararr(j).sgarray(k).nstrokes%loop over each stroke
                nstrokearray(m).points=X(v).chararr(j).sgarray(k).strokearray(l).points;
                m=m+1;
                
            end
        end
    end
    
    %smooting of input word
    
    if mod(v,10)==0
        clf
    end
    c=2*(v);
   
    subplot(5,4,(c-1)
    pause
    hold on
    for p=1:length(nstrokearray)
        nstrokearray(p) = SmoothStrk(nstrokearray(p));
        plot(nstrokearray(p).points(:,1),nstrokearray(p).points(:,2));
        q=q+1;
    end
    hold off
    
    
    length(nstrokearray)
    csg.stroke(1).points=nstrokearray(1).points;
    nstrokearray(1)=[];
    
    minx=[];
    for i=1:length(nstrokearray)
        minx=[minx min(nstrokearray(i).points(:,1))];
    end
    [~,ind]=sort(minx);
    test=nstrokearray;
    nstrokearray=nstrokearray(ind);
    length(nstrokearray)
    
    for i=1:length(nstrokearray)
        if isnan(nstrokearray(i).points())
            uncl = uncl -1;
        end
        val1=isabove(nstrokearray(i),csg.stroke(1)); %Checking if the stroke is a top stroke
        if val1==1
            csg.stroke=[csg.stroke nstrokearray(i)];    
        end
        
        val2=isbelow(nstrokearray(1),csg.stroke(1)); %Checking if the stroke is a bottom stroke
        if val2==1
            csg.stroke=[csg.stroke nstrokearray(i)];
        end
        
        
        val3=isauxormain(nstrokearray(i),csg.stroke(1));
        if val3==1
            Baux=isBaux(nstrokearray(i));    %Checking if the stroke is a baseline auxiliary stroke
            if Baux==1
                csg.stroke=[csg.stroke nstrokearray(i)];
                val4=0;
            else
                hold on;
                subplot(5,4,c)
                for f=1:length(csg.stroke)
                    plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));
                    
                end
                hold off;
                val4=1;
                
                nsg=nstrokearray(i);
                
                if colorc == 5
                    colorc=0;
                end
                colorc=colorc+1;
                
                % newXstrokearray=cat(1,newXstrokearray,csg.stroke);
                csg.stroke(:)=[];
                csg.stroke(1)=nsg;
                if i>1 && uncl>0
                    if isequal(nstrokearray(i-1), unclassified(uncl))
                        val1=isabove(nstrokearray(i-1),nstrokearray(i)); %Checking if the stroke is a top stroke
                        if val1==1
                            csg.stroke=[csg.stroke nstrokearray(i-1)];
                        end
                        val2=isbelow(nstrokearray(i-1),nstrokearray(i)); %Checking if the stroke is a bottom stroke
                        if val2==1
                            csg.stroke=[csg.stroke nstrokearray(i-1)];
                        end
                    end
                end
            end
        end
        if val1==0 && val2 ==0 && val3==0
            uncl=uncl+1;
            unclassified.stroke(uncl) = nstrokearray(i);
        end            
        hold on;
        subplot(5,4,c)
        
        for f=1:length(csg.stroke)
            plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));   % if last strokearray is next main
            
        end
        hold off;
        if i == length(nstrokearray)
            csg.stroke(:)=[];
        end
    end
    length(nstrokearray)
end




load('complete_wrong_data_730')
q=1;
colorc=1;
colors=['r','g','b','y','m'];
% y=[];
nstrokearray=[];

v=1;
for v=1:10
    m=1;
    for j=1:X(v).nchars
        for k=1:X(v).chararr(j).nsgs%Loop over each sgarray in the character
            for l=1:X(v).chararr(j).sgarray(k).nstrokes%loop over each stroke
                nstrokearray(m).points=X(v).chararr(j).sgarray(k).strokearray(l).points;
                m=m+1;
                
            end
        end
    end
    
       segchar=1;
    
    c=2*v;
    subplot(5,4,c-1)
    hold on
    for p=1:length(nstrokearray)
       
        %smooting of input word
    nstrokearray(p)=SmoothStrk(nstrokearray(p));
    
        plot(nstrokearray(p).points(:,1),nstrokearray(p).points(:,2));
        q=q+1;
    end
    hold off
    
    
    
    csg.stroke(1).points=nstrokearray(1).points;
    
    nstrokearray(1)=[];
    
    minx=[];
    for i=1:length(nstrokearray)
        minx=[minx min(nstrokearray(i).points(:,1))];
    end
    [~,ind]=sort(minx);
    %test=nstrokearray;
    nstrokearray=nstrokearray(ind);
    
    indx=0;
    
    for i=1:length(nstrokearray)
        
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
                apoint=csg.stroke(1).points;
               bpoint=nstrokearray(i).points;
                
                %a=deal(vertcat(csg.stroke(1).points,nstrokearray(i).points))
               
               %test1.stroke(1).points=nstrokearray(i).points;
               %test1.stroke(1).points=[]
               test1.stroke(1).points=vertcat(csg.stroke(1).points,nstrokearray(i).points);
               % [test.stroke]=deal(vertcat(csg.stroke(1),nstrokearray(i)));
                 if indx >=1
                   for ind3=1:indx
                    neglectedval=checkstrayobject(unclassified.stroke(ind3),test1.stroke);
                                        
                    if neglectedval==1
                        csg.stroke=[csg.stroke unclassified.stroke(indx)];
                    end
                   end
                end
                
                %test1.stroke(1).points=[];
                
                
                
            else
                
                val4=1;
                
                nsg=nstrokearray(i);
                
                hold on;
                subplot(5,4,c)
                for f=1:length(csg.stroke)
                    plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));
                    
                end
                hold off;
                
                
                if colorc == 5
                    colorc=0;
                end
                colorc=colorc+1;
                for in2=1:length(csg.stroke)
                Xnew(v).chararr(segchar).sgarray.strokearray(in2).points=csg.stroke(in2).points;  %creating new structure after segmentation
                end           
                segchar=segchar+1;
                % newXstrokearray=cat(1,newXstrokearray,csg.stroke);
                csg.stroke(:)=[];
                csg.stroke(1)=nsg;
                if indx >=1
                   for ind3=1:indx
                    neglectedval=checkstrayobject(unclassified.stroke(ind3),nsg);
                                        
                    if neglectedval==1
                        csg.stroke=[csg.stroke unclassified.stroke(indx)];
                    end
                   end
                end
                
            end
            
        else 
            indx=indx+1;
            unclassified.stroke(indx)=nstrokearray(i);
        end
        hold on;
        subplot(5,4,c)
        
        for f=1:length(csg.stroke)
            plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));   % if last strokearray is next main
            
        end
        hold off;
        
        if i == length(nstrokearray)
            csg.stroke(:)=[];
            nstrokearray(:)=[];
        end
    end
end



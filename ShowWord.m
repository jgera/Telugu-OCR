
load('complete_wrong_data_730')
 m=1;
 colorc=1;
 colors=['r','g','b','y','m'];
   % y=[];
    nstrokearray=[];
    c=0;
    for v=1:10
for j=1:X(v).nchars
for k=1:X(v).chararr(j).nsgs%Loop over each sgarray in the character
         for l=1:X(v).chararr(j).sgarray(k).nstrokes%loop over each stroke
             nstrokearray(m).points=X(v).chararr(j).sgarray(k).strokearray(l).points;
             m=m+1;
            
         end
          end
end
c=c+1;
 subplot(5,4,c);
 for p=1:length(nstrokearray)
  plot(nstrokearray(p).points(:,1),nstrokearray(p).points(:,2));hold on;
 end
 c=c+1;
 csg.stroke(1).points=nstrokearray(1).points;
 
 nstrokearray(1)=[];
 
 minx=[];
for i=1:length(nstrokearray)
    minx=[minx min(nstrokearray(i).points(:,1))];
end
[~,ind]=sort(minx);
test=nstrokearray;
nstrokearray=nstrokearray(ind);

for i=1:length(nstrokearray)
    
    val1=isabove(nstrokearray(i),csg.stroke(1))%Checking if the stroke is a top stroke
         if val1==1
        csg.stroke=[csg.stroke nstrokearray(i)];
   % nstrokearray(i)=[];
         end
         
         val2=isbelow(nstrokearray(1),csg.stroke(1))%Checking if the stroke is a bottom stroke
        if val2==1
        csg.stroke=[csg.stroke nstrokearray(i)];
       % nstrokearray(i)=[];
        end
        
        
        val3=isauxormain(nstrokearray(i),csg.stroke(1))
      if val3==1
           Baux=isBaux(nstrokearray(i))    %Checking if the stroke is a baseline auxiliary stroke
        if Baux==1
            csg.stroke=[csg.stroke nstrokearray(i)];
        %nstrokearray(i)=[];
       val4=0
        else
            subplot(5,4,c);
            for f=1:length(csg.stroke)
                 plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));
                 hold on;
             end
            val4=1
            
             nsg=nstrokearray(i);
            
             
             colorc=colorc+1;
          
          % newXstrokearray=cat(1,newXstrokearray,csg.stroke);      
          csg.stroke(:)=[];
          csg.stroke(1)=nsg;
          subplot(5,4,c);
         for f=1:length(csg.stroke)
                 plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));   
                 hold on;
             end
        
        end
       
        
      end
      subplot(5,4,c);
      for f=1:length(csg.stroke)
                 plot(csg.stroke(f).points(:,1),csg.stroke(f).points(:,2),colors(colorc));   % if last strokearray is next main
                 hold on;
      end
      
end
    end
    
   


    
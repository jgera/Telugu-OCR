function [tmpFeats,ftx,fty]=extractfeatures(a)

%b=[a(:,1)-min(a(:,1)),-a(:,2)+max(a(:,2))];

%L=max(a(:,2))-min(a(:,2));
%W=max(a(:,1))-min(a(:,1));
 
%Xtmp=(b(:,1)/L)*100;
%Ytmp=(b(:,2)/W)*100;

%xint=interp(Xtmp,4);
%yint=interp(Ytmp,4);

%x=smootharray(xint);
%y=smootharray(yint);

%plot(x,y)
%pause

x = a(:,1);
y = a(:,2);

[arr_size,z]=size(x);
tmpXPts=x+y;
tmpYPts=y-x;

nFeatCnt=1;
lw=6;BMPWIN=6;
for i=1:arr_size,
  
    
    if (i==1),
        
  %      X=tmpXPts((lw*(i-1)+1):lw*i);
   %     Y=tmpYPts((lw*(i-1)+1):lw*i);
   
      
%    p = polyfit(X,Y,1);
%   yfinal = p(1,2)+p(1,1)*X(lw);

        yfinal = tmpYPts(lw);
        if((tmpXPts(lw) >= tmpXPts(1)) && (yfinal < tmpYPts(1))) 
            nFeature=1;  
        end
        if(tmpXPts(lw)<tmpXPts(1) && yfinal >= tmpYPts(1))
            nFeature=5;   
        end
        if(tmpXPts(lw)<tmpXPts(1) && yfinal <tmpYPts(1)) 
            nFeature=3;   
        end
        if(tmpXPts(lw)>= tmpXPts(1) && yfinal >= tmpYPts(1))
            nFeature=7; 
        end        
        tmpFeats(nFeatCnt)=nFeature;
        ftx(nFeatCnt) = x(i);
        fty(nFeatCnt) = y(i);
        nFeatCnt=nFeatCnt+1;
   
    end %end of (if(i==1)) case    

    if (i==arr_size)
        
%        X=tmpXPts(arr_size-lw:arr_size);
%        Y=tmpYPts(arr_size-lw:arr_size);
        
%        p = polyfit(X,Y,1);
 %       yfinal = p(1,2) + p(1,1)*X(1);
        yfinal = tmpYPts(arr_size-lw);
        if(tmpXPts(arr_size-lw) >= tmpXPts(arr_size) && yfinal < tmpYPts(arr_size)) 
            nFeature=1;
        end  
        if(tmpXPts(arr_size-lw)<tmpXPts(arr_size) && yfinal >= tmpYPts(arr_size))
            nFeature=5;   
        end
        if(tmpXPts(arr_size-lw)<tmpXPts(arr_size) && yfinal <tmpYPts(arr_size)) 
            nFeature=3;
        end
        if(tmpXPts(arr_size-lw) >= tmpXPts(arr_size) && yfinal >= tmpYPts(arr_size))
            nFeature=7; 
        end
        tmpFeats(nFeatCnt)=nFeature;
        ftx(nFeatCnt) = x(i);
        fty(nFeatCnt) = y(i);
        nFeatCnt=nFeatCnt+1;
    
    end  %end of (i==arr_size) case

    
    if(i > BMPWIN) && (i < arr_size-BMPWIN+1)
        
        
            tmpx =  x(i-BMPWIN:i+BMPWIN);
            tmpy =  y(i-BMPWIN:i+BMPWIN);
        
        %	//First look for a cusp...
       % retval=IsCusp2(tmpx, tmpy, 2*BMPWIN+1 );
       retval=IsCusp3(tmpx, tmpy);
        if (retval==1)
%            keyboard
%            [tmpx tmpy]
            
            tmpFeats(nFeatCnt)= 17;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
         
        else % //if it is not a cusp, look for a BUMP
        
            flg1=1;
            flg2=1; 
            flg3=1; 
            flg4=1;
            flg5=1;
            flg6=1; 
            flg7=1;
            flg8=1;
        
        for(te=i-BMPWIN:i+BMPWIN)
            
            if(y(te) < y(i)) 
                flg1=0;
            end
            if(y(te) > y(i)) 
                flg2=0;
            end
            if(x(te) < x(i))
                flg3=0;
            end
            if(x(te) > x(i)) 
                flg4=0;
            end
            if(tmpYPts(te)<tmpYPts(i)) 
                flg5=0;
            end
            if(tmpYPts(te)>tmpYPts(i)) 
                flg6=0;
            end
            if(tmpXPts(te)<tmpXPts(i)) 
                flg7=0;
            end
            if(tmpXPts(te)>tmpXPts(i)) 
                flg8=0;
            end 
        end %of line for(te=i-BMPWIN:i+BMPWIN)
        if(flg5)		%// -45 deg line , negative bump 
            
            tmpFeats(nFeatCnt)= 10;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        if(flg6)		%// -45 deg line , positive bump 
            
            tmpFeats(nFeatCnt)= 14;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        if(flg7)		%//+45 deg line , negative bump 
            
            tmpFeats(nFeatCnt)= 12;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
       if(flg8)		%// +45 deg line , positive bump 
            
            tmpFeats(nFeatCnt)= 16;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        if(flg1)		%// Horizontal line , negative bump 
            
            tmpFeats(nFeatCnt)= 11;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        if(flg2)		%// Horizontal line , positive bump 
            
            tmpFeats(nFeatCnt)= 15;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        if(flg3)	%	// Vertical line , positive bump 
            
            tmpFeats(nFeatCnt)= 13;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
       if(flg4)		%// Vertical line , negative bump 
            
            tmpFeats(nFeatCnt)= 9;
            ftx(nFeatCnt) = x(i);
            fty(nFeatCnt) = y(i);
            nFeatCnt=nFeatCnt+1;
        end
        
    end
end

end


%plot(x,y,'r-',ftx,fty,'o')
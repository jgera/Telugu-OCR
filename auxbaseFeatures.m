function sfs =  auxbaseFeatures(ch)
        
          strk = ch    % stroke array
             
          strkint = InterpStrk(strk, 2);   % here n=2 i.e. we are interpolating and reducing computation by taking 2 points in place of 1.
                                             %after interpolation points
                                             %are saved in strkint
            z = strkint.points;
            size(z);     % we are not storing in any variable the value of size(z)
            %plot(z(:,1), z(:,2),'g')

            strksm = SmoothStrk(strkint);
            zsm = strksm.points;
           % plot(zsm(:,1), zsm(:,2), 'g')

            sfs = determinefeatures(strksm);     % here changes are needed...only required cases should be computed.
          
           
         end
         
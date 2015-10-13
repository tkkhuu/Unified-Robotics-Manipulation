% Final Project MATLAB Code
%Written by Team 10
%lex Caracappa, Tri Khuu, Saraj Pirasmepulkul

clc; close all; clear all;
%this is the code you are running

% Configure the serial port, set the com port and baud rate here
% Use the serial doc to help find the appropriate parameters
serialIn = serial('/dev/cu.usbmodem1411', 'Baudrate', 9600, 'Terminator', 'CR/LF');

% This code reads in serial values real time and plots it
% Open the serial port. Be sure to close it later or you may have trouble
% re-opening
fopen(serialIn)

% Check the serial configuration if you want
fig = figure();
axes_handle=axes('DataAspectRatioMode','manual','CameraPositionMode', 'manual','Parent',fig,'XLim', [-1 1], 'YLim', [-1 1], 'ZLim',[-1 1], 'XLimMode', 'manual', 'YLimMode', 'manual','ZLimMode', 'manual');
% disp (serialIn)
% h.figure1=figure('Name','Shimmer 1');
% h.axes=axes('Linewidth',(4),'XGrid','on','YGrid','on','ZGrid','on','XLim',[-2 2],'YLim',[-2 2],'ZLim',[-2 2]);
% grid on;
% hold on;
% axis([-2.00 3.00 -2.00 300 -2.00 2.00]);
%             baseline=line([-200 0],[-200 -200],'LineWidth',2);
%             baselink=line([0 0], [-200 0],'LineWidth',2);
% Sample - run in infinie loop
while(1)
    %     Wait until a line has at least 24 bytes (in this example, can set to
    %     what you need)
    if (serialIn.BytesAvailable >= 24 )
        %         Include error checking to avoid it crashing
        %try
        %             Read the serial buffer, configure the input parsing as
        %             required for your data format
        
        fwrite(serialIn, 1); %write binary code to data
        fprintf(serialIn, '%c',41); %write text to data
        
        %             from this website https://inventrom.wordpress.com/2014/05/26/atmega-uart-tranfer-data-to-matlab-via-usb/
        
        %             theta1, theta2
        a = (fscanf(serialIn, '%f,%f,%f,%f'))';
        %             set(h.figure1,'CurrentAxes',h.axes);
        q0 = a(:,1);%(360*(a(:,1)))/1023;
        q1 = a(:,2);
        q2 = a(:,3);
        q3 = a(:,4);
        rotMatrix = [(1 - 2*q2^2 - 2*q3^2), 2*(q1*q2 + q0*q3), 2*(q1*q3 - q0*q2);
            2*(q1*q2 - q0*q3), (1 - 2*q1^2 - 2*q3^2), 2*(q2*q3 + q0*q1);
            2*(q1*q3 + q0*q2), 2*(q2*q3 - q0*q1), (1 - 2*q1^2 - 2*q2^2)];
        r = [1; 0; 0];
        a = rotMatrix * r;
        
        
        vector_x = [0;a(1)]';
        vector_y = [0;a(2)]';
        vector_z = [0;a(3)]';
        plot3(axes_handle,vector_x, vector_y, vector_z, 'red')
        temp = sprintf('%f, %f, %f, %f\r\n', q0,q1,q2,q3);
        
        disp(temp)
        
        %                    [x,y] = armKinematics(theta1, theta2, a1, a2);
        
        
        %link1=line([0 vector_x],[0 vector_y],'Marker', 'o','MarkerEdgeColor','k','MarkerFaceColor', 'g', 'MarkerSize', 10,'color','red','LineWidth',2);
        %link2=line([0 vector_x],[0 vector_z],'Marker', 'o','MarkerEdgeColor','k','MarkerFaceColor', 'g', 'MarkerSize', 10,'color','red','LineWidth',2);
        %plot(link1)%,[a1*cos(theta1) x], [a1*sin(theta1) y]);
        
        pause(.1);
        %delete(link1)
        %                        delete(link2)
        
        %catch MExc
        %disp(MExc)
    end
    
end

%end


% To disconnect the serial port object from the serial port.
% This will not happen automatically in this sample because of the inifinite loop
fclose(serialIn);

% You can also call this to remove the initialized post
delete (serialIn);

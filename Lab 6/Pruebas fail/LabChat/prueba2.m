function varargout = prueba2(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @prueba2_OpeningFcn, ...
                   'gui_OutputFcn',  @prueba2_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before prueba2 is made visible.
function prueba2_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
clc;
pue.BaudRate=9600;
handles.pue=pue;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes prueba2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = prueba2_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
cont=cellstr(get(hObject,'String'));
pop=get(hObject,'Value');
if (pop==2)
    delete(instrfind({'port'},{'COM1'}));
    handles.pue=serial('COM1');   
end
if (pop==3)
    delete(instrfind({'port'},{'COM2'}));
    handles.pue=serial('COM2');   
end
if (pop==4)
    delete(instrfind({'port'},{'COM3'}));
    handles.pue=serial('COM3');   
end
if (pop==5)
    delete(instrfind({'port'},{'COM4'}));
    handles.pue=serial('COM4');   
end
if (pop==6)
    delete(instrfind({'port'},{'COM5'}));
    handles.pue=serial('COM5');   
end
if (pop==7)
    delete(instrfind({'port'},{'COM6'}));
    handles.pue=serial('COM6');   
end
if (pop==8)
    delete(instrfind({'port'},{'COM8'}));
    handles.pue=serial('COM8');   
end
if (pop==9)
    delete(instrfind({'port'},{'COM10'}));
    handles.pue=serial('COM10');   
end
if (pop==10)
    delete(instrfind({'port'},{'COM12'}));
    handles.pue=serial('COM12');   
end
if (pop==11)
    delete(instrfind({'port'},{'COM14'}));
    handles.pue=serial('COM14');   
end


% --- Executes on button press in buttonCon.
function buttonCon_Callback(hObject, eventdata, handles)
% hObject    handle to buttonCon (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fopen(handles.pue);
disp('Port opened')


% --- Executes on button press in ButtonDesc.
function ButtonDesc_Callback(hObject, eventdata, handles)
% hObject    handle to ButtonDesc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fclose(handles.pue);
disp('Port closed')


% --- Executes on button press in Envio.
function Envio_Callback(hObject, eventdata, handles)
% hObject    handle to Envio (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fwrite(handles.pue,get(handles.edit2,'string'));
disp('data Sent.....')



% --- Executes on button press in Lectura.
function Lectura_Callback(hObject, eventdata, handles)
% hObject    handle to Lectura (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fwrite(handles.pue,get(handles.edit2,'string'));
disp('reading data.....')



% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

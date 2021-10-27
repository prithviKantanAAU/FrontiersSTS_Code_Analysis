%% Read CSV Data

% Get info on CSV filenames and number
path = 'D:\PhD\Year 1\STS Study\Perceptual Test\MATLAB ANALYSIS\Expt Logs';

% Get information about what's inside your folder, delete path variable
myfiles = dir(path);

% Get the filenames and folders of all files and folders inside the folder
filenames={myfiles(:).name}';
filefolders={myfiles(:).folder}';

% Get only those files that have a csv extension
csvfiles=filenames(endsWith(filenames,'.csv'));
csvfolders=filefolders(endsWith(filenames,'.csv'));

% Make a cell array of strings containing the full file locations
files=fullfile(csvfolders,csvfiles);
num_Files = length(files);
METADATA_num_Participants = num_Files;

% Figure Save Path
savePath = 'D:\PhD\Year 1\STS Study\Perceptual Test\MATLAB ANALYSIS\Data Analysis Plots\';

%% Data Structures

% Basic Info About Experiment Structure
METADATA_num_Blocks = 6;
METADATA_num_Patterns = 6;
METADATA_num_Reps = 3;

% Order Matrix
Block_Orders = zeros(METADATA_num_Participants, METADATA_num_Blocks);

% MSoph Vector
MSoph_Subj = zeros(1,METADATA_num_Participants);

% 4D format - Block, Rep, Pattern, Participant
Tensor_Response = zeros(METADATA_num_Blocks,METADATA_num_Reps,METADATA_num_Patterns,METADATA_num_Participants);
Tensor_Confidence = zeros(METADATA_num_Blocks,METADATA_num_Reps,METADATA_num_Patterns,METADATA_num_Participants);
Tensor_ResponseTime = zeros(METADATA_num_Blocks,METADATA_num_Reps,METADATA_num_Patterns,METADATA_num_Participants);

%% Reading CSV Data Into Matrices

for participantIdx = 1 : METADATA_num_Participants
    
    % Put data in cell table
    csvPath = strcat(path,'\',char(csvfiles{participantIdx}));
    [~,~,fileTable] = xlsread(csvPath);
    
    % Get size of table
    [file_numRows,file_numCols] = size(fileTable);
    
    % Update the present header being measured
    presentHeader = '';
    lineIdx_presentHeader = 0;
    
    % Go through table matrix rows
    for lineNum = 1 : file_numRows
        
        % Check if first column is a string, update header if so
        if iscellstr(fileTable(lineNum,1))
            presentHeader = string(fileTable(lineNum,1));
            lineIdx_presentHeader = lineNum;    
        end
        
        % Store OMSI
        if strcmp(presentHeader,'OMSI Index')
                MSoph_Subj(participantIdx) = cell2mat(fileTable(lineNum,2));
        end
        
        % Store Block Order
        if strcmp(presentHeader,'Block Order') && ~iscellstr(fileTable(lineNum,1))
            for colNum = 1 : METADATA_num_Blocks
            Block_Orders(participantIdx,colNum) = cell2mat(fileTable(lineNum,colNum));
            end
        end
        
        % Store Responses
        for blockNum = 1 : METADATA_num_Blocks
            choiceHeader = string(strcat('Choice - Block',{' '},int2str(blockNum - 1)));
            if strcmp(presentHeader,choiceHeader) && ~iscellstr(fileTable(lineNum,1))
                
                for colNum = 1 : METADATA_num_Reps
                    Tensor_Response(blockNum,colNum,lineNum - lineIdx_presentHeader,participantIdx)...
                        = max(1,cell2mat(fileTable(lineNum,colNum)));
                end
            end
        end
        
        % Store Confidence
        for blockNum = 1 : METADATA_num_Blocks
            choiceHeader = string(strcat('Confidence - Block',{' '},int2str(blockNum - 1)));
            if strcmp(presentHeader,choiceHeader) && ~iscellstr(fileTable(lineNum,1))
                
                for colNum = 1 : METADATA_num_Reps
                    Tensor_Confidence(blockNum,colNum,lineNum - lineIdx_presentHeader,participantIdx)...
                        = cell2mat(fileTable(lineNum,colNum));
                end
            end
        end       
        
        % Store Reaction Time
        for blockNum = 1 : METADATA_num_Blocks
            choiceHeader = string(strcat('Response Time - Block',{' '},int2str(blockNum - 1)));
            if strcmp(presentHeader,choiceHeader) && ~iscellstr(fileTable(lineNum,1))
                
                for colNum = 1 : METADATA_num_Reps
                    Tensor_ResponseTime(blockNum,colNum,lineNum - lineIdx_presentHeader,participantIdx)...
                        = cell2mat(fileTable(lineNum,colNum));
                end
            end
        end   
    end
end
Block_Orders = Block_Orders + 1;
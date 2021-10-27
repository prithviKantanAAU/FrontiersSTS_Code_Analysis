%% Blockwise Confusion Matrices

blockwise_Responses_Matrix = [];
blockwise_ConfPerc_Matrix = [];
blockwise_RespTime_Matrix = [];
blockwise_ParticipantIdx_Matrix = [];

correctClasses_PROTO = [1 2 3 4 5 6];
correctClasses = repmat(correctClasses_PROTO,1,METADATA_num_Participants*METADATA_num_Reps);
OUTCOME_ConfMat_Classification = zeros(6,6,6);
OUTCOME_ConfMat_Precision_Blk_Pat = zeros(6,6);
OUTCOME_ConfMat_Recall_Blk_Pat = zeros(6,6);
OUTCOME_ConfMat_FMeasr_Blk_Pat = zeros(6,6);

for i = 1 : METADATA_num_Blocks
    
    blockwise_Responses_Vector = [];
    blockwise_ConfPerc_Vector = [];
    blockwise_RespTime_Vector = [];
    participantIdx_Vector = [];
    
    for j = 1 : METADATA_num_Participants
        temp_Blockwise_Responses = transpose(squeeze(Tensor_Response(i,:,:,j)));
        temp_Blockwise_Responses = temp_Blockwise_Responses(:);
        
        temp_Blockwise_ConfPerc = transpose(squeeze(Tensor_Confidence(i,:,:,j)));
        temp_Blockwise_ConfPerc = temp_Blockwise_ConfPerc(:) ./ conPerc_Part_MEAN(j) .*100 - 100;
        
        temp_Blockwise_RespTime = transpose(squeeze(Tensor_ResponseTime(i,:,:,j)));
        temp_Blockwise_RespTime = temp_Blockwise_RespTime(:) ./ rspTime_Part_MEAN(j) .*100 - 100;
        
        blockwise_Responses_Vector = horzcat(blockwise_Responses_Vector,temp_Blockwise_Responses');
        blockwise_ConfPerc_Vector = horzcat(blockwise_ConfPerc_Vector,temp_Blockwise_ConfPerc');
        blockwise_RespTime_Vector = horzcat(blockwise_RespTime_Vector,temp_Blockwise_RespTime');
        participantIdx_Vector = horzcat(participantIdx_Vector, j * ones(1,length(temp_Blockwise_Responses)));
    end
    
    blockwise_Responses_Matrix = vertcat(blockwise_Responses_Matrix,blockwise_Responses_Vector);
    blockwise_ConfPerc_Matrix = vertcat(blockwise_ConfPerc_Matrix,blockwise_ConfPerc_Vector);
    blockwise_RespTime_Matrix = vertcat(blockwise_RespTime_Matrix,blockwise_RespTime_Vector);
    blockwise_ParticipantIdx_Matrix = vertcat(blockwise_ParticipantIdx_Matrix,participantIdx_Vector);
    
    C_temp = confusionmat(correctClasses,blockwise_Responses_Matrix(i,:));
    sum(C_temp(:))
    figure
    labels = {'(P1) Slow','(P2) Slow-Fast','(P3) Failed Attempts','(P4) Freezing','(P5) Jerky','(P6) Unstable Ankles'};
    labels = categorical(labels);
    confusionchart(C_temp,labels)
    title(sprintf('Block %d', i));
    savefig(strcat(savePath,sprintf('Block-Wise Confusion Matrices\\ConfMat - Block %d.fig',i)));
    
    for k = 1 : METADATA_num_Patterns
        for l = 1 : METADATA_num_Patterns
          OUTCOME_ConfMat_Classification(k,l,i) = C_temp(k,l);  
        end
    end
end

% Calculate Precision and Recall

for i = 1 : METADATA_num_Blocks
    for j = 1 : METADATA_num_Patterns
        OUTCOME_ConfMat_Precision_Blk_Pat(i,j) = OUTCOME_ConfMat_Classification(j,j,i) / sum(OUTCOME_ConfMat_Classification(:,j,i));
        OUTCOME_ConfMat_Recall_Blk_Pat(i,j) = OUTCOME_ConfMat_Classification(j,j,i) / sum(OUTCOME_ConfMat_Classification(j,:,i));
        OUTCOME_ConfMat_FMeasr_Blk_Pat(i,j) = 2 * OUTCOME_ConfMat_Precision_Blk_Pat(i,j) * OUTCOME_ConfMat_Recall_Blk_Pat(i,j)...
                                                / (OUTCOME_ConfMat_Precision_Blk_Pat(i,j) + OUTCOME_ConfMat_Recall_Blk_Pat(i,j));
    end
end

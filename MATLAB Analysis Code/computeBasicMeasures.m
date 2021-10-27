med_OMSI = median(MSoph_Subj);
for i = 1 : 1 : length(MSoph_Subj)
    if MSoph_Subj(i) >= med_OMSI
        MSoph_Grp(i) = 2;
    else
        MSoph_Grp(i) = 1;
    end
end

% Overall Classification Accuracy
METADATA_trials_PerBlock = METADATA_num_Reps * METADATA_num_Patterns;
METADATA_trials_Total = METADATA_trials_PerBlock * METADATA_num_Blocks;

OUTCOME_accPerc_Subj_MEAN = zeros(1, METADATA_num_Participants);
OUTCOME_accPerc_Subj_MEAN_REPWISE = zeros(METADATA_num_Participants, METADATA_num_Reps);
OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel = zeros(METADATA_num_Participants, METADATA_num_Reps);

OUTCOME_accPerc_Subj_Blk_REPWISE = zeros(METADATA_num_Blocks,METADATA_num_Reps,METADATA_num_Participants);
OUTCOME_accPerc_Subj_Blk_REPWISE_Rel = zeros(METADATA_num_Blocks,METADATA_num_Reps,METADATA_num_Participants);
OUTCOME_accPerc_Subj_Blk = zeros(METADATA_num_Participants,METADATA_num_Blocks);
OUTCOME_accPerc_Subj_Blk_ORDERED = zeros(METADATA_num_Participants,METADATA_num_Blocks);

OUTCOME_conPerc_Subj_Blk = zeros(METADATA_num_Participants,METADATA_num_Blocks);
OUTCOME_conPerc_REPWISE = zeros(METADATA_num_Blocks * METADATA_num_Participants * METADATA_num_Patterns, METADATA_num_Reps);
OUTCOME_conPerc_Blk_REPWISE = zeros(METADATA_num_Blocks, METADATA_num_Reps);
OUTCOME_conPerc_Subj_Blk_ORDERED = zeros(METADATA_num_Participants,METADATA_num_Blocks);

OUTCOME_rspTime_Subj_Blk = zeros(METADATA_num_Participants,METADATA_num_Blocks);
OUTCOME_rspTime_REPWISE = zeros(METADATA_num_Blocks * METADATA_num_Participants * METADATA_num_Patterns, METADATA_num_Reps);
OUTCOME_rspTime_Blk_REPWISE = zeros(METADATA_num_Blocks, METADATA_num_Reps);
OUTCOME_rspTime_Subj_Blk_ORDERED = zeros(METADATA_num_Participants,METADATA_num_Blocks);

num_CorResp_TOTAL_REP = zeros(1, METADATA_num_Reps);
num_CorResp_Blk_REP = zeros(METADATA_num_Blocks, METADATA_num_Reps);

% Overall and Repwise Accuracy
for i = 1 : METADATA_num_Participants
    num_CorrectResponses_TOTAL = 0;
    
    for m = 1 : METADATA_num_Reps
        num_CorResp_TOTAL_REP(m) = 0;
    end
    
    for j = 1 : METADATA_num_Patterns
        for k = 1 : METADATA_num_Blocks
            for l = 1 : METADATA_num_Reps                                           % REP NUMBER
                if Tensor_Response(k,l,j,i) == j
                     num_CorrectResponses_TOTAL = num_CorrectResponses_TOTAL + 1;
                     num_CorResp_TOTAL_REP(l) = num_CorResp_TOTAL_REP(l) + 1;
                end
            end
        end
    end
    OUTCOME_accPerc_Subj_MEAN(i) = num_CorrectResponses_TOTAL * 100.0 / METADATA_trials_Total;
    
    for m = 1 : METADATA_num_Reps
        OUTCOME_accPerc_Subj_MEAN_REPWISE(i,m) = num_CorResp_TOTAL_REP(m) * 100.0 / METADATA_trials_Total * METADATA_num_Reps;
        OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel(i,m) = ((num_CorResp_TOTAL_REP(m)) * 100.0 / METADATA_trials_Total * METADATA_num_Reps) / OUTCOME_accPerc_Subj_MEAN(i) * 100 - 100;
    end
end

% Blockwise Accuracy, Confidence, Time // ORDERED ACCURACY // Repwise
% Accuracy
for i = 1 : METADATA_num_Participants                                                                              % I = PARTICIPANT
    
    num_CorResp_Blk_REP(:,:) = 0;
    for j = 1 : METADATA_num_Blocks                                                                                % J = BLOCK
        
        num_CorrectResponses_BLOCK = 0;
        totalConfidence = 0;
        totalTime = 0; 
        
        for k = 1 : METADATA_num_Patterns                                                                          % K = PATTERN
            for l = 1 : METADATA_num_Reps                                                                          % L = REP
                if Tensor_Response(j,l,k,i) == k
                    num_CorrectResponses_BLOCK = num_CorrectResponses_BLOCK + 1;
                    num_CorResp_Blk_REP(j,l) = num_CorResp_Blk_REP(j,l) + 1;
                end
                
                OUTCOME_conPerc_REPWISE((i-1) * METADATA_num_Blocks * METADATA_num_Patterns + ...
                    (j-1)* METADATA_num_Patterns + k, l) = Tensor_Confidence(j,l,k,i);
                
                OUTCOME_rspTime_REPWISE((i-1) * METADATA_num_Blocks * METADATA_num_Patterns + ...
                    (j-1)* METADATA_num_Patterns + k, l) = Tensor_ResponseTime(j,l,k,i);
                
                OUTCOME_conPerc_Blk_REPWISE(j,l) = OUTCOME_conPerc_Blk_REPWISE(j,l) + Tensor_Confidence(j,l,k,i);
                OUTCOME_rspTime_Blk_REPWISE(j,l) = OUTCOME_rspTime_Blk_REPWISE(j,l) + Tensor_ResponseTime(j,l,k,i);
                
                totalConfidence = totalConfidence + Tensor_Confidence(j,l,k,i);
                totalTime = totalTime + Tensor_ResponseTime(j,l,k,i);
            end
        end
        
        OUTCOME_accPerc_Subj_Blk(i,j) = num_CorrectResponses_BLOCK * 100.0 / METADATA_trials_PerBlock;        
        OUTCOME_conPerc_Subj_Blk(i,j) = totalConfidence / METADATA_trials_PerBlock;
        OUTCOME_rspTime_Subj_Blk(i,j) = totalTime / METADATA_trials_PerBlock;
        
        OUTCOME_accPerc_Subj_Blk_ORDERED(i,Block_Orders(i,j)) = OUTCOME_accPerc_Subj_Blk(i,j);
        OUTCOME_conPerc_Subj_Blk_ORDERED(i,Block_Orders(i,j)) = OUTCOME_conPerc_Subj_Blk(i,j);
        OUTCOME_rspTime_Subj_Blk_ORDERED(i,Block_Orders(i,j)) = OUTCOME_rspTime_Subj_Blk(i,j);
    end
    
    num_CorResp_Blk_REP = num_CorResp_Blk_REP / METADATA_trials_PerBlock * METADATA_num_Reps * 100.0;
    OUTCOME_accPerc_Subj_Blk_REPWISE(:,:,i) = num_CorResp_Blk_REP;
    
     for m = 1 : METADATA_num_Blocks
    OUTCOME_accPerc_Subj_Blk_REPWISE_Rel(m,:,i) = OUTCOME_accPerc_Subj_Blk_REPWISE(m,:,i) / OUTCOME_accPerc_Subj_MEAN(i) * 100 - 100;
     end
end

for i = 1 : METADATA_num_Patterns * METADATA_num_Blocks
OUTCOME_conPerc_SoundClip_REPWISE(i,:) = mean(OUTCOME_conPerc_REPWISE(i : METADATA_num_Patterns * METADATA_num_Blocks : end,:));
OUTCOME_rspTime_SoundClip_REPWISE(i,:) = mean(OUTCOME_rspTime_REPWISE(i : METADATA_num_Patterns * METADATA_num_Blocks : end,:));
end

OUTCOME_accPerc_Blk_MEAN = mean(OUTCOME_accPerc_Subj_Blk);
OUTCOME_accPerc_MEAN_Blk_REPWISE_Rel = mean(OUTCOME_accPerc_Subj_Blk_REPWISE_Rel,3);
COMBO_accPerc_MSoph = [OUTCOME_accPerc_Subj_Blk MSoph_Grp'];

OUTCOME_conPerc_Blk_REPWISE = OUTCOME_conPerc_Blk_REPWISE / (METADATA_num_Patterns * METADATA_num_Participants);
OUTCOME_rspTime_Blk_REPWISE = OUTCOME_rspTime_Blk_REPWISE / (METADATA_num_Patterns * METADATA_num_Participants);
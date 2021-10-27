%METADATA_num_Blocks = 6;
%METADATA_num_Patterns = 6;
%METADATA_num_Reps = 3;
%METADATA_num_Participants = size(Tensor_Response,4);
% Figure Save Path
% savePath = 'D:\PhD\Year 1\STS Study\Perceptual Test\MATLAB ANALYSIS\Data Analysis Plots\';

OUTCOME_conPerc_Subj_Pattern = zeros(METADATA_num_Participants,METADATA_num_Patterns);
OUTCOME_rspTime_Subj_Pattern = zeros(METADATA_num_Participants,METADATA_num_Patterns);

OUTCOME_conPerc_Subj_Pattern_Blk = zeros(METADATA_num_Participants,METADATA_num_Patterns,METADATA_num_Blocks);
OUTCOME_rspTime_Subj_Pattern_Blk = zeros(METADATA_num_Participants,METADATA_num_Patterns,METADATA_num_Blocks);

for i = 1 : METADATA_num_Participants
    for j = 1 : METADATA_num_Patterns
        for k = 1 : METADATA_num_Blocks
            for l = 1 : METADATA_num_Reps
                
                OUTCOME_conPerc_Subj_Pattern(i,j) = OUTCOME_conPerc_Subj_Pattern(i,j) + Tensor_Confidence(k,l,j,i);
                OUTCOME_rspTime_Subj_Pattern(i,j) = OUTCOME_rspTime_Subj_Pattern(i,j) + Tensor_ResponseTime(k,l,j,i);
                
                OUTCOME_conPerc_Subj_Pattern_Blk(i,j,k) = OUTCOME_conPerc_Subj_Pattern_Blk(i,j,k) + Tensor_Confidence(k,l,j,i);
                OUTCOME_rspTime_Subj_Pattern_Blk(i,j,k) = OUTCOME_rspTime_Subj_Pattern_Blk(i,j,k) + Tensor_ResponseTime(k,l,j,i);
                
            end
        end
    end
end
;
OUTCOME_conPerc_Subj_Pattern = OUTCOME_conPerc_Subj_Pattern ./ (METADATA_num_Blocks * METADATA_num_Reps);
mean_conPerc_Part = mean(OUTCOME_conPerc_Subj_Pattern,2);
OUTCOME_conPerc_Subj_Pattern_Rel = OUTCOME_conPerc_Subj_Pattern ./ mean_conPerc_Part .*100 - 100;
OUTCOME_rspTime_Subj_Pattern = OUTCOME_rspTime_Subj_Pattern ./ (METADATA_num_Blocks * METADATA_num_Reps);
mean_rspTime_Part = mean(OUTCOME_rspTime_Subj_Pattern,2);
OUTCOME_rspTime_Subj_Pattern_Rel = OUTCOME_rspTime_Subj_Pattern ./ mean_rspTime_Part .*100 - 100;
OUTCOME_conPerc_Subj_Pattern_Blk = OUTCOME_conPerc_Subj_Pattern_Blk ./ METADATA_num_Reps;
OUTCOME_rspTime_Subj_Pattern_Blk = OUTCOME_rspTime_Subj_Pattern_Blk ./ METADATA_num_Reps;

% Confidence
figure
violinplot(OUTCOME_conPerc_Subj_Pattern);
title('Mean Confidence (%) per STS Pattern')
xticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Movement Pattern')
ylabel('Confidence (%)')
savefig(strcat(savePath,'Pattern-Wise Outcomes\Confidence - Abs.fig'));

figure
violinplot(OUTCOME_conPerc_Subj_Pattern_Rel);
title('Normalized Confidence per STS Pattern')
xticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Movement Pattern')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Pattern-Wise Outcomes\Confidence - Rel.fig'));

figure
for i = 1 : METADATA_num_Blocks
    subplot(2,3,i)
    violinplot(OUTCOME_conPerc_Subj_Pattern_Blk(:,:,i) ./ mean_conPerc_Part .*100 - 100);
    title(sprintf('Block %d',i));
    yline(0,'-.r')
    ylim([-70 80])
end
sgtitle('Normalized Confidence per STS Pattern - Blockwise')
savefig(strcat(savePath,'Pattern-Wise Outcomes\\Confidence - Abs - Blkwise.fig'));

% Response Time
figure
violinplot(OUTCOME_rspTime_Subj_Pattern);
title('Mean Response Time (sec) per STS Pattern')
xticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Movement Pattern')
ylabel('Response Time (sec)')
savefig(strcat(savePath,'Pattern-Wise Outcomes\Response Time - Abs.fig'));

figure
violinplot(OUTCOME_rspTime_Subj_Pattern_Rel);
title('Normalized Response Time per STS Pattern')
xticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
xlabel('Movement Pattern')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Pattern-Wise Outcomes\Response Time - Rel.fig'));

figure
for i = 1 : METADATA_num_Blocks
    subplot(2,3,i)
    violinplot(OUTCOME_rspTime_Subj_Pattern_Blk(:,:,i) ./ mean_rspTime_Part .*100 - 100);
    title(sprintf('Block %d',i));
    yline(0,'-.r')
    ylim([-70 80])
end
sgtitle('Normalized Response Time per STS Pattern - Blockwise')
savefig(strcat(savePath,'Pattern-Wise Outcomes\\Response Time - Abs - Blkwise.fig'));

%% Pattern-wise F-Measure

blockwise_Responses_Matrix = [];

correctClasses_PROTO = [1 2 3 4 5 6];
correctClasses = repmat(correctClasses_PROTO,1,METADATA_num_Reps);
OUTCOME_ConfMat_Precision_Blk_Pat_2 = zeros(METADATA_num_Participants,METADATA_num_Patterns,METADATA_num_Blocks);
OUTCOME_ConfMat_Recall_Blk_Pat_2 = zeros(METADATA_num_Participants,METADATA_num_Patterns,METADATA_num_Blocks);
OUTCOME_ConfMat_FMeasr_Blk_Pat_2 = zeros(METADATA_num_Participants,METADATA_num_Patterns,METADATA_num_Blocks);

for i = 1 : METADATA_num_Blocks    
    for j = 1 : METADATA_num_Participants
        temp_Blockwise_Responses = transpose(squeeze(Tensor_Response(i,:,:,j)));
        temp_Blockwise_Responses = temp_Blockwise_Responses(:);
        confmat_Part = confusionmat(correctClasses,temp_Blockwise_Responses);
        
        for k = 1 : METADATA_num_Patterns
            OUTCOME_ConfMat_Precision_Blk_Pat_2(j,k,i) = confmat_Part(k,k) / sum(confmat_Part(:,k));
            if isnan(OUTCOME_ConfMat_Precision_Blk_Pat_2(j,k,i)) 
                OUTCOME_ConfMat_Precision_Blk_Pat_2(j,k,i) = 0;
            end
            OUTCOME_ConfMat_Recall_Blk_Pat_2(j,k,i) = confmat_Part(k,k) / sum(confmat_Part(k,:));
        end
    end
end

precision_MEAN_Pattern = mean(OUTCOME_ConfMat_Precision_Blk_Pat_2,3);
recall_MEAN_Pattern = mean(OUTCOME_ConfMat_Recall_Blk_Pat_2,3);

OUTCOME_ConfMat_FMeasr_Pat = 2 * precision_MEAN_Pattern .* recall_MEAN_Pattern ./ (precision_MEAN_Pattern + recall_MEAN_Pattern);
figure
violinplot(OUTCOME_ConfMat_FMeasr_Pat);
xticklabels({'Slow','Slow-Fast','Failed Attempts','Freezing','Jerky','Unstable Ankles'});
title('F1 Score per STS Pattern')
xlabel('Movement Pattern')
ylabel('F1 Score')
savefig(strcat(savePath,'Pattern-Wise Outcomes\Mean F1-Score.fig'));

clear OUTCOME_ConfMat_Precision_Blk_Pat_2
clear OUTCOME_ConfMat_Recall_Blk_Pat_2
clear OUTCOME_ConfMat_FMeasr_Blk_Pat_2
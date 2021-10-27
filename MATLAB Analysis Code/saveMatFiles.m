%% Datasets for SPSS

clc

load('distPat_Hyp.mat')
savePath_Data = 'D:\PhD\Year 1\STS Study\Perceptual Test\MATLAB ANALYSIS\SPSS Datasets\';
dataMat = [];

dataMat = [OUTCOME_accPerc_Subj_Blk OUTCOME_accPerc_Subj_MEAN' MSoph_Subj' MSoph_Grp']; 
save(strcat(savePath_Data,'Accuracy\Acc_Abs_Mapping_MSoph.mat'),'dataMat');

dataMat = OUTCOME_accPerc_Subj_Blk_Rel; 
save(strcat(savePath_Data,'Accuracy\Acc_Norm_Mapping.mat'),'dataMat');

dataMat = OUTCOME_accPerc_Subj_Blk_ORDERED;
save(strcat(savePath_Data,'Accuracy\Acc_Abs_Block.mat'),'dataMat');

dataMat = OUTCOME_accPerc_Subj_Blk_ORDERED_Rel;
save(strcat(savePath_Data,'Accuracy\Acc_Norm_Block.mat'),'dataMat');

dataMat = OUTCOME_accPerc_Subj_MEAN_REPWISE;
save(strcat(savePath_Data,'Accuracy\Acc_Abs_Rep.mat'),'dataMat');

dataMat = OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel;
save(strcat(savePath_Data,'Accuracy\Acc_Norm_Rep.mat'),'dataMat');

dataMat = OUTCOME_ConfMat_FMeasr_Pat;
save(strcat(savePath_Data,'Accuracy\FMeas_Abs_Pattern.mat'),'dataMat');

dataMat = transpose(OUTCOME_ConfMat_FMeasr_Blk_Pat);
save(strcat(savePath_Data,'Accuracy\FMeas_Block_Pattern.mat'),'dataMat');

% Confidence
dataMat = [OUTCOME_conPerc_Subj_Blk MSoph_Subj' MSoph_Grp'];
save(strcat(savePath_Data,'Confidence\Conf_Abs_Mapping_MSoph.mat'),'dataMat');

dataMat = OUTCOME_conPerc_Subj_Blk_ORDERED;
save(strcat(savePath_Data,'Confidence\Conf_Abs_Block.mat'),'dataMat');

dataMat = OUTCOME_conPerc_Subj_Pattern;
save(strcat(savePath_Data,'Confidence\Conf_Abs_Pattern.mat'),'dataMat');

dataMat = [OUTCOME_conPerc_SoundClip_REPWISE clusterVec_conPerc_repWise_SFiles];
save(strcat(savePath_Data,'Confidence\Conf_Abs_Rep.mat'),'dataMat');

dataMat = OUTCOME_conPerc_Subj_Blk_ORDERED_Rel;
save(strcat(savePath_Data,'Confidence\Conf_Norm_Block.mat'),'dataMat');

dataMat = OUTCOME_conPerc_Subj_Blk_Rel;
save(strcat(savePath_Data,'Confidence\Conf_Norm_Mapping.mat'),'dataMat');

dataMat = OUTCOME_conPerc_Subj_Pattern_Rel;
save(strcat(savePath_Data,'Confidence\Conf_Norm_Pattern.mat'),'dataMat');

% Response Time
dataMat = [OUTCOME_rspTime_Subj_Blk MSoph_Subj' MSoph_Grp'];
save(strcat(savePath_Data,'Response Time\Time_Abs_Mapping_MSoph.mat'),'dataMat');

dataMat = OUTCOME_rspTime_Subj_Blk_ORDERED;
save(strcat(savePath_Data,'Response Time\Time_Abs_Block.mat'),'dataMat');

dataMat = OUTCOME_rspTime_Subj_Pattern;
save(strcat(savePath_Data,'Response Time\Time_Abs_Pattern.mat'),'dataMat');

dataMat = [OUTCOME_rspTime_SoundClip_REPWISE clusterVec_rspTime_repWise_SFiles];
save(strcat(savePath_Data,'Response Time\Time_Abs_Rep.mat'),'dataMat');

dataMat = OUTCOME_rspTime_Subj_Blk_ORDERED_Rel;
save(strcat(savePath_Data,'Response Time\Time_Norm_Block.mat'),'dataMat');

dataMat = OUTCOME_rspTime_Subj_Blk_Rel;
save(strcat(savePath_Data,'Response Time\Time_Norm_Mapping.mat'),'dataMat');

dataMat = OUTCOME_rspTime_Subj_Pattern_Rel;
save(strcat(savePath_Data,'Response Time\Time_Norm_Pattern.mat'),'dataMat');

dataMat = ALL_Part_Conf_Time_RtWrng;
save(strcat(savePath_Data,'Miscellaneous\Conf_Time_RtWrong.mat'),'dataMat');

temp = OUTCOME_ConfMat_FMeasr_Blk_Pat';
dataMat = [distinctPat_Hyp mean(OUTCOME_conPerc_SoundClip_REPWISE,2) ...
    mean(OUTCOME_rspTime_SoundClip_REPWISE,2) temp(:)];
save(strcat(savePath_Data,'Miscellaneous\SndFile_DistPat_Predict.mat'),'dataMat');
clear temp
%% Data Dump

save(strcat(savePath,'MAT FILES\Data_Tensors.mat'),...
    'Tensor_Confidence','Tensor_Response','Tensor_ResponseTime','MSoph_Subj');

save(strcat(savePath,'MAT FILES\Outcomes.mat'),...
    'OUTCOME_accPerc_Subj_Blk'...
    ,'OUTCOME_accPerc_Subj_Blk_Rel'...
    ,'OUTCOME_accPerc_Subj_Blk_ORDERED'...
    ,'OUTCOME_accPerc_Subj_Blk_ORDERED_Rel'...
    ,'OUTCOME_accPerc_MEAN_Blk_REPWISE_Rel'...
    ,'OUTCOME_accPerc_Subj_Blk_REPWISE'...
    ,'OUTCOME_accPerc_Subj_Blk_REPWISE_Rel'...
    ,'OUTCOME_accPerc_Subj_MEAN'...
    ,'OUTCOME_accPerc_Subj_MEAN_REPWISE'...
    ,'OUTCOME_accPerc_Subj_MEAN_REPWISE_Rel'...
    ,'OUTCOME_ConfMat_FMeasr_Blk_Pat'...
    ,'OUTCOME_ConfMat_Precision_Blk_Pat'...
    ,'OUTCOME_ConfMat_Recall_Blk_Pat'...
    ,'OUTCOME_conPerc_Blk_REPWISE'...
    ,'OUTCOME_conPerc_REPWISE'...
    ,'OUTCOME_conPerc_Subj_Blk'...
    ,'OUTCOME_conPerc_Subj_Blk_Rel'...
    ,'OUTCOME_rspTime_Blk_REPWISE'...
    ,'OUTCOME_rspTime_REPWISE'...
    ,'OUTCOME_rspTime_Subj_Blk'...
    ,'OUTCOME_rspTime_Subj_Blk_Rel'...
    );
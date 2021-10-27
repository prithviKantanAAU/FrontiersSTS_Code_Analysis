%% Correlation - Response Time and Confidence (RELATIVE)

forCorr_Conf_Vec = OUTCOME_conPerc_Subj_Blk_Rel(:);
forCorr_Time_Vec = OUTCOME_rspTime_Subj_Blk_Rel(:);
forCorr_AGG = [forCorr_Conf_Vec forCorr_Time_Vec];
figure
[R_Time_Conf, R_Time_Conf_P] = corrplot(forCorr_AGG,'varNames',{'Confi', 'Time'});
savefig(strcat(savePath,'Block-Wise Outcomes\Correlation - Time vs Confidence.fig'));

% MSoph v/s accuracy

figure
[R_Acc_MSoph, R_Acc_MSoph_P] = corrplot([OUTCOME_accPerc_Subj_MEAN' MSoph_Subj'],'varNames',{'Accuracy', 'MSoph Index'});
savefig(strcat(savePath,'Block-Wise Outcomes\Correlation - Accuracy vs MSoph.fig'));
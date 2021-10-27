%% Compare Relative Confidence and Relative Response Time between CORRECT and INCORRECT

ALL_CorrectClasses_VECTOR = repmat(correctClasses,1,METADATA_num_Blocks);
ALL_Responses_VECTOR = blockwise_Responses_Matrix(:);
ALL_ConfPerc_VECTOR = blockwise_ConfPerc_Matrix(:);
ALL_RespTime_VECTOR = blockwise_RespTime_Matrix(:);
ALL_RightWrong_VECTOR = zeros(1,length(ALL_CorrectClasses_VECTOR));
ALL_ParticipantIdx_VECTOR = blockwise_ParticipantIdx_Matrix(:);
CORRECT_ConfPerc_VECTOR = [];
WRONG_ConfPerc_VECTOR = [];
CORRECT_RespTime_VECTOR = [];
WRONG_RespTime_VECTOR = [];
ALL_Part_Conf_Time_RtWrng = [];

for i = 1 : length(ALL_CorrectClasses_VECTOR)
    if ALL_Responses_VECTOR(i) == ALL_CorrectClasses_VECTOR(i)
        ALL_RightWrong_VECTOR(i) = 1;
        CORRECT_ConfPerc_VECTOR = [CORRECT_ConfPerc_VECTOR ALL_ConfPerc_VECTOR(i)];
        CORRECT_RespTime_VECTOR = [CORRECT_RespTime_VECTOR ALL_RespTime_VECTOR(i)];
    else
        ALL_RightWrong_VECTOR(i) = 2;
        WRONG_ConfPerc_VECTOR = [WRONG_ConfPerc_VECTOR ALL_ConfPerc_VECTOR(i)];
        WRONG_RespTime_VECTOR = [WRONG_RespTime_VECTOR ALL_RespTime_VECTOR(i)];
    end
end

CORRECT_WRONG_VECTOR = transpose(horzcat(ones(1,length(CORRECT_ConfPerc_VECTOR)),zeros(1,length(WRONG_ConfPerc_VECTOR))));
MATRIX_conPerc_rspTime_rtWrong = ...
    [transpose(horzcat(CORRECT_ConfPerc_VECTOR,WRONG_ConfPerc_VECTOR))...
    transpose(horzcat(CORRECT_RespTime_VECTOR,WRONG_RespTime_VECTOR))...
    CORRECT_WRONG_VECTOR
    ];

MATRIX_CORRECT_WRONG_ConfPerc = NaN(length(CORRECT_ConfPerc_VECTOR),2);
MATRIX_CORRECT_WRONG_RespTime = NaN(length(CORRECT_ConfPerc_VECTOR),2);

for i = 1 : length(CORRECT_ConfPerc_VECTOR)
    MATRIX_CORRECT_WRONG_ConfPerc(i,1) = CORRECT_ConfPerc_VECTOR(i);
    MATRIX_CORRECT_WRONG_RespTime(i,1) = CORRECT_RespTime_VECTOR(i);
end

for j = 1 : length(WRONG_ConfPerc_VECTOR)
    MATRIX_CORRECT_WRONG_ConfPerc(j,2) = WRONG_ConfPerc_VECTOR(j);
    MATRIX_CORRECT_WRONG_RespTime(j,2) = WRONG_RespTime_VECTOR(j);
end

ALL_Part_Conf_Time_RtWrng = [ALL_ParticipantIdx_VECTOR ALL_ConfPerc_VECTOR...
    ALL_RespTime_VECTOR ALL_RightWrong_VECTOR'];

figure
%boxplot(MATRIX_CORRECT_WRONG_ConfPerc)
violinplot(MATRIX_CORRECT_WRONG_ConfPerc)
title('Normalized Confidence (Correct v/s Wrong Answers)')
xticklabels({'Correct','Incorrect'});
xlabel('Nature of Response')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Right vs Wrong Answers\Confidence Comparison.fig'));

figure
%boxplot(MATRIX_CORRECT_WRONG_RespTime)
violinplot(MATRIX_CORRECT_WRONG_RespTime)
title('Normalized Response Time (Correct v/s Wrong Answers)')
xticklabels({'Correct','Incorrect'});
xlabel('Nature of Response')
ylabel('% of Participant Mean')
yline(0,'-.r','Participant Mean')
savefig(strcat(savePath,'Right vs Wrong Answers\Response Time Comparison.fig'));
% Speed Corrector visualisation
% Used for Climbing Clock documentation

correct_speed = 400;
speeds = [correct_speed - 100;
    correct_speed + 80;
    correct_speed + 30;
    correct_speed - 25;
    correct_speed + 13;
    correct_speed + 3;
    correct_speed - 1];
cycles = 1:length(speeds);

stem(cycles, speeds, 'LineWidth', 1);
xlim([0, length(cycles) + 0.5]);
ylim([0, 600]);
yline(correct_speed, '--', 'Correct Speed', 'LabelHorizontalAlignment', 'left');
ylabel('Speed', 'FontSize', 12);
xlabel('Cycle', 'FontSize', 12);
yticklabels({});
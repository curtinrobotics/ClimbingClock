% Code for generating heat regulator machine learning figure
% For Climbing Clock project

T0 = 10; % max temperature for no power
T1 = 15; % min acceptable temperature
T2 = 25; % max acceptable temperature
key_tempts = [T0, T1, T2];
minPower = 200;
maxPower = 700;

dtempt = 0.5;
tempt = (T0 - 5):dtempt:(T2 + 10);

power = zeros(length(tempt));

for i = 1:length(tempt)
    power(i) = calcPower(tempt(i), T0, minPower, maxPower);
end

plot(tempt, power, 'LineWidth', 1);
xlim([T0 - 2, T2 + 10]);
ylim([minPower - 50, maxPower + 50]);
ylabel('Power', 'FontSize', 12);
xlabel('Temperature (\circC)', 'FontSize', 12);
xticks([T0, T1, T2]);
xticklabels({'T_0', 'T_1', 'T_2'});
yticks([minPower, maxPower]);
yticklabels({'Min', 'Max'});

good_tempt_x = [T1, T2, T2, T1];
good_tempt_y = [-500, -500, 5000, 5000];
patch(good_tempt_x, good_tempt_y, 'green', 'FaceAlpha', 0.3);

good_tempt = {'Target', 'temperature'};
low_tempt = {'Cooling', 'too much'};
high_tempt = {'Cooling', 'too little'};
text((T2 + T1) / 2, 450, good_tempt, 'HorizontalAlignment', 'center', 'FontWeight', 'bold');
text(T1 - 4, 450, low_tempt, 'HorizontalAlignment', 'center', 'FontWeight', 'bold');
text(T2 + 5, 450, high_tempt, 'HorizontalAlignment', 'center', 'FontWeight', 'bold');

yline(minPower, '--');
yline(maxPower, '--');

function pow = calcPower(tempt, T0, minPower, maxPower)
    if tempt < T0
        pow = minPower;
    else
        pow = (tempt - T0)^2 + minPower;
        
        if pow > maxPower
            pow = maxPower;
        end
    end
end
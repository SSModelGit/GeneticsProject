%ploclose tR
title_str = 'Ex 1 Screening Policy Simulation: ';

mut_params_screen
diseaseData
screenEffectiveness = [0,0.25,0.5,0.75,1.0];
for i = 1:length(screenEffectiveness)
    mut.screen.efficiency = screenEffectiveness(i);
    sim('mut_screen')
    res.deltaPop(i)  = f_T.signals(1).values(end) - f_T.signals(1).values(1);
    res.FinalAlleleRecessive(i) = f_T.signals(4).values(end);
   
    figure
    subplot(2,1,1)
    plot(f_T.time,f_T.signals(1).values/1e6)

    ylabel('Total Population (millions)')
    title([title_str, 'Screen Eff = ', ...
        num2str(screenEffectiveness(i))]);
    grid
    subplot(2,1,2)
    plot(f_T.time, f_T.signals(2).values,'b')
    hold
    plot(f_T.time, f_T.signals(3).values,'k')
    plot(f_T.time, f_T.signals(4).values,'r')
    hold
    xlabel('years')
    ylabel('Mutation Allele Frequency (%)')
    legend('homozygous Dominant freq', 'heterozygous freq', 'homozygous Recessive freq')
    grid
end

figure
scatter(screenEffectiveness,res.deltaPop*1e-6,((res.FinalAlleleRecessive).^2)*1,'filled')
curAxis = axis;
curAxis(1)= -.1;
axis(curAxis);
xlabel('Screening Effectiveness')
ylabel('Population Change (Millions) in 50 years')
title([title_str, 'Potential Policy Impact of Genetic Screening on Homozygous Allele'])
legend('size of bubble reflects size of Homozygous Recessive Frequency')
grid


        function nav = GoToTarget2(nav,j)
            %METHOD1 Simulador
            nav.p = plot(nav.r(1),nav.r(2),'o');
            xlim([0 25])
            ylim([0 25])
            nav.p.XDataSource = 'nav.r(1)';
            nav.p.YDataSource = 'nav.r(2)';
            linkdata on;

            for t = 1:10
                nav.r(1) = nav.r(1) + 1;
                display(nav.r(1))
                refreshdata
                pause(0.1)
            end

        end
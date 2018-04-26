# #!/bin/bash

# problem1
echo INIT SEQUENTIAL EXPERIMENTS!!
# for i in {1..1}
# do
# 	for problem in problem1 
# 	do 
# 		for exec in sequential parallel
# 		do
# 			for metric in runtime miss
# 			do
# 				for tec in DOD  OOD
# 				do
# 					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7
# 					do
# 						if [ $exec == "sequential" ]
# 						then 
# 							echo command:
# 							echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							echo finish execution steep
# 						 else
# 						 	echo command:
# 						 	echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	echo finish execution steep
# 						 fi
# 					done
# 				done
# 			done
# 		done
# 	done
# done

# problem2
# for i in {1..1}
# do
# 	for problem in problem2
# 	do 
# 		for exec in sequential parallel
# 		do
# 			for metric in runtime miss
# 			do
# 				for tec in DOD DOD_ordered DOD_property_ordered OOD
# 				do
# 					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7
# 					do
# 						if [ $exec == "sequential" ]
# 						then 
# 							echo command:
# 							echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							echo finish execution steep
# 						 else
# 						 	echo command:
# 						 	echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	echo finish execution steep
# 						 fi
# 					done
# 				done
# 			done
# 		done
# 	done
#  done

# problem3
for i in {1..1}
do
        for problem in problem3
        do
                for extra in e0
                do
                        for exec in sequential parallel
                        do
                                for metric in runtime miss
                                do
                                        for tec in OOD DOD
                                        do
                                                for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7
                                                do
                                                        if [ $exec == "sequential" ]
                                                        then 
                                                                echo command:
                                                                echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
                                                                ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
                                                                echo finish execution steep
                                                        else
                                                                echo command:
                                                                echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
                                                                ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
                                                                echo finish execution steep
                                                        fi

                                                done
                                        done
                                done
                        done
                done

		# for extra in e125 e150 e175 e200 e400 e600
  #               do
  #                       for exec in sequential parallel
  #                       do
  #                               for metric in runtime miss
  #                               do
  #                                       for tec in OOD
  #                                       do
  #                                               for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7
  #                                               do
  #                                                       if [ $exec == "sequential" ]
  #                                                       then 
  #                                                               echo command:
  #                                                               echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
  #                                                               ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
  #                                                               echo finish execution steep
  #                                                       else
  #                                                               echo command:
  #                                                               echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
  #                                                               ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric][$extra] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit\_$extra.txt
  #                                                               echo finish execution steep
  #                                                       fi

  #                                               done
  #                                       done
  #                               done
  #                       done
  #               done
        done
done

# problem4
# for i in {1..1}
# done
# 	for problem in problem4 
# 	do 
# 		for exec in sequential
# 		do
# 			for metric in runtime miss
# 			do
# 				for tec in DOD  OOD
# 				do
# 					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7
# 					do
# 						if [ $exec == "sequential" ]
# 						then 
# 							echo command:
# 							echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 							echo finish execution steep
# 						 else
# 						 	echo command:
# 						 	echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
# 						 	echo finish execution steep
# 						 fi
# 					done
# 				done
# 			done
# 		done
# 	done
#  done

echo FINISH EXPERIMENTS!!
# #!/bin/bash
# for i in {1..30}                                                                                                                                                                                                                                                               
# do                                                                                                                                                                                                                                                                             
	for problem in problem1 problem2 problem3
	do 
		for exec in sequential parallel
		do
			for metric in runtime miss
			do
				for tec in DOD OOD
				do
					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7                                                                                                                                                                            
					do
						if [ $exec == "sequential" ]
						then 
							echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp /results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						else
							echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp /results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						fi
					done
				done	
			done
		done
	done                                                                                                                                                                                                                                                           
# done


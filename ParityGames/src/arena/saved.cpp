
  for (vector<int>::iterator i = randomized_vertices_list.begin(); i!=randomized_vertices_list.end(); i++) {
    cout << *i << " ";
  }
  cout <<"\n";
  getchar();
  

  cout<< "Post shuffle";
  for (vector<int>::iterator i = randomized_vertices_list.begin(); i!=randomized_vertices_list.end(); i++) {
    cout << *i << " ";
  }
  cout <<"\n";
  getchar();



OLD RF code

  // case RandomFacet: 
  //   cout << "RandomFacet\n"; 
  //     if (improvements.get_strictly_improving_vertices().empty()) {
  // 	for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
  // 	  int curr_v_id = (*it).get_id();
  // 	  PLAYER curr_v_player = (*it).get_player();
  // 	  if (curr_v_player == pl) {
  // 	    sigma_prime.set_decision(curr_v_id, sigma.get_decision(curr_v_id));
  // 	  } 
  // 	}
  //     }
  //     else {
  // 	vector<int>::iterator key_vertex;
  // 	bool flag = false;
  // 	for (vector<int>::iterator it = randomized_vertices_list.begin(); it != randomized_vertices_list.end(); it++) {
 
  // 	  PLAYER curr_v_player =  get_vertex(*it).get_player();
  // 	  if (curr_v_player == pl) {
  // 	    if (flag) {
  // 	      sigma_prime.set_decision(*it, sigma.get_decision(*it));
  // 	    }
  // 	    else {
  // 	      if (improvements.get_strictly_improving_vertices().find(*it) != improvements.get_strictly_improving_vertices().end()) 
  // 		{
  // 		  key_vertex = it;
  // 		  //		  key_vertex++;
  // 		  flag = true;
  // 		}
  // 	      int opt = *improvements.get_switches(*it).rbegin();
  // 	      sigma_prime.set_decision(*it, opt);
  // 	    }
  // 	  }
  // 	}
  // 	random_shuffle(randomized_vertices_list.begin(), key_vertex);
  //     } 
  //     break;
      





      // { // assert block 
      // 	Valuation v_old = computeValue_two(sigma, pl);
      // 	Valuation v_new = computeValue_two(sigma_prime, pl);
	
      //   for (vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      // 	  int curr_v_id = (*it).get_id();
      // 	  PLAYER curr_v_player = (*it).get_player();
	  
      // 	  if (curr_v_player == pl) {
      // 	    Value old_val = v_old.get_value(curr_v_id);
      // 	    Value new_val = v_new.get_value(curr_v_id);
	    
      // 	    if (pl == odd) {
      // 	      assert (new_val <= old_val); 
      // 	    }
      // 	    else {
      // 	      assert(new_val >= old_val);
      // 	    }
      // 	  }
      // 	}
      // } //end assert 

      // int random_impr_vertex = get_sample(improvements.get_strictly_improving_vertices());
      // sigma_prime.set_decision(random_impr_vertex, get_sample(improvements.get_switches(random_impr_vertex)));
      
      // assert(flag);

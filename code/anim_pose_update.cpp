if (m_obj->GetGameObjectType() == SCA_IObject::OBJ_ARMATURE)
{
	BL_ArmatureObject *obj = (BL_ArmatureObject*)m_obj;
	obj->GetPose(&m_pose);

	// Extract the pose from the action
	{
		Object *arm = obj->GetArmatureObject();
		bPose *temp = arm->pose;

		arm->pose = m_pose;

		PointerRNA ptrrna;
		RNA_id_pointer_create(&arm->id, &ptrrna);

		animsys_evaluate_action(&ptrrna, m_action, NULL, m_localtime);

		arm->pose = temp;
	}

	// Handle blending between armature actions
	if (m_blendin && m_blendframe<m_blendin)
	{
		IncrementBlending(curtime);

		// Calculate weight
		float weight = 1.f - (m_blendframe/m_blendin);

		// Blend the poses
		game_blend_poses(m_pose, m_blendinpose, weight, ACT_BLEND_BLEND);
	}


	// Handle layer blending
	if (m_layer_weight >= 0)
	{
		obj->GetMRDPose(&m_blendpose);
		game_blend_poses(m_pose, m_blendpose, m_layer_weight, m_blendmode);
	}

	obj->SetPose(m_pose);

	obj->SetActiveAction(NULL, 0, curtime);
}

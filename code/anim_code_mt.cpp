static void update_anim_thread_func(TaskPool *pool,
									void *taskdata,
									int UNUSED(threadid))
{
	KX_GameObject *gameobj, *child;
	CListValue *children;
	bool needs_update;
	double curtime = *(double*)BLI_task_pool_userdata(pool);

	gameobj = (KX_GameObject*)taskdata;

	// Non-armature updates are fast enough, so just update them
	needs_update = gameobj->GetGameObjectType() != SCA_IObject::OBJ_ARMATURE;

	if (!needs_update) {
		// If we got here, we're looking to update an armature, so check its
		// children meshes to see if we need to bother with a more expensive
		// pose update
		children = gameobj->GetChildren();

		bool has_mesh = false, has_non_mesh = false;

		// Check for meshes that haven't been culled
		for (int j=0; j<children->GetCount(); ++j) {
			child = (KX_GameObject*)children->GetValue(j);

			if (!child->GetCulled()) {
				needs_update = true;
				break;
			}

			if (child->GetMeshCount() == 0)
				has_non_mesh = true;
			else
				has_mesh = true;
		}

		// If we didn't find a non-culled mesh, check to see
		// if we even have any meshes, and update if this
		// armature has only non-mesh children.
		if (!needs_update && !has_mesh && has_non_mesh)
			needs_update = true;

		children->Release();
	}

	if (needs_update)
		gameobj->UpdateActionManager(curtime);
}

void KX_Scene::UpdateAnimations(double curtime)
{
	TaskPool *pool = BLI_task_pool_create(KX_GetActiveEngine()->GetTaskScheduler(),
										  &curtime);

	for (int i=0; i<m_animatedlist->GetCount(); ++i) {
		BLI_task_pool_push(pool,
						   update_anim_thread_func,
						   m_animatedlist->GetValue(i),
						   false,
						   TASK_PRIORITY_LOW);
	}

	BLI_task_pool_work_and_wait(pool);
	BLI_task_pool_free(pool);
}

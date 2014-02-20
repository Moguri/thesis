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

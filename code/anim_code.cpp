void KX_Scene::UpdateAnimations(double curtime)
{
	// Update any animations
	for (int i=0; i<m_animatedlist->GetCount(); ++i)
		((KX_GameObject*)m_animatedlist->GetValue(i))->UpdateActionManager(curtime);
}

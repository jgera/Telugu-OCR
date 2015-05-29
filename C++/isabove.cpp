int isabove(stroke1, stroke2)
{
	if isoverlappping(stroke1, stroke2) == 1
	{
		if min(stroke1.points(:,2))>(max(stroke2.points(:,2))-0.2*(range(stroke2.points(:,2))))
		{
			return 1
		}
		else
			return 0
	}
	else
		return 0
}
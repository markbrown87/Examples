from django import template

register = template.Library()

@register.filter
def keyvalue(dict, key):    
    return dict[key]

@register.filter
def addstr(arg1, arg2):
    """concatenate arg1 & arg2"""
    return str(arg1) + str(arg2)

@register.filter
def listelem(list,index):
	return list[index]
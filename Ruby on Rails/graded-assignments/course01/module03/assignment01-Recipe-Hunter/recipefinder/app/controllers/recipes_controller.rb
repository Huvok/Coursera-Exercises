class RecipesController < ApplicationController
  def index
    @search_param = params[:search] || 'chocolate'

    @recipes = Recipe.for(@search_param)
  end
end

'use strict';
angular.module('confusionApp')
    .controller('MenuController', ['$scope', 'menuFactory', function($scope, menuFactory) 
    {

        $scope.tab = 1;
        $scope.filtText = '';
        $scope.showDetails = false;
        $scope.showMenu = false;
        $scope.message = "Loading ...";
        menuFactory.getDishes().query(
            function(response) 
            {
                $scope.dishes = response;
                $scope.showMenu = true;
            },
            
            function(response) 
            {
                $scope.message = "Error: "+response.status + " " + response.statusText;
            }
        );
        
        $scope.select = function(setTab) 
        {
            $scope.tab = setTab;

            if (setTab === 2) 
            {
                $scope.filtText = "appetizer";
            } 
            else if (setTab === 3) 
            {
                this.filtText = "mains";
            }
            else if (setTab === 4) 
            {
                this.filtText = "dessert";
            }
            else 
            {
                this.filtText = "";
            }
        };

        $scope.isSelected = function (checkTab) 
        {
            return ($scope.tab === checkTab);
        };

        $scope.toggleDetails = function() 
        {
            $scope.showDetails = !$scope.showDetails;
        };
    }])

    .controller('ContactController', ['$scope', function($scope) 
    {
        $scope.feedback = {mychannel:"", firstName:"", lastName:"", agree:false, email:"" };
        
        var channels = [{value:"tel", label:"Tel."}, {value:"Email", label:"Email"}];
        
        $scope.channels = channels;
        $scope.invalidChannelSelection = false;
    }])

    .controller('FeedbackController', ['$scope', function($scope)  
    {
        $scope.sendFeedback = function() 
        {
            console.log($scope.feedback);
            
            if ($scope.feedback.agree &&
                $scope.feedback.mychannel == "")
            {
                $scope.invalidChannelSelection = true;
                console.log('incorrect');
            }
            else
            {
                $scope.invalidChannelSelection = false;
                $scope.feedback = 
                {
                    mychannel:"", firstName:"",
                    lastName:"", agree:false, email:"" 
                };
                $scope.feedback.mychannel="";
                $scope.feedbackForm.$setPristine();
                console.log($scope.feedback);
            }
        };
    }])

    .controller('DishDetailController', ['$scope', '$stateParams', 'menuFactory', function($scope, $stateParams, menuFactory) 
    {        
        $scope.dish = {};
        $scope.showDish = false;
        $scope.message="Loading ...";
        $scope.dish = menuFactory.getDishes().get({id:parseInt($stateParams.id, 10)})
.$promise.then(
            function(response)
            {
                $scope.dish = response;
                $scope.showDish = true;
            },
            
            function(response) 
            {
                $scope.message = "Error: "+response.status + " " + response.statusText;
            }
        );
    }])

    /* If using angular-route
    .controller('DishDetailController', ['$scope', '$routeParams', 'menuFactory', function($scope, $routeParams, menuFactory) 
    {
        var dish = menuFactory.getDish(parseInt($routeParams.id,10)); 
        $scope.dish = dish;
    }])*/

    .controller('DishCommentController', ['$scope', 'menuFactory', function($scope, menuFactory) 
    {        
        $scope.formComment = 
        {
            author: "",
            rating: 5,
            comment: "",
            date:""
        };

        $scope.submitComment = function () 
        {
            $scope.formComment.date = new Date().toISOString();
            $scope.dish.comments.push($scope.formComment);
            menuFactory.getDishes().update({id: $scope.dish.id}, $scope.dish);
            $scope.formComment = 
            {
                author: "",
                rating: 5,
                comment: "",
                date: ""
            };
            
            $scope.commentForm.$setPristine();
        }
    }])

    .controller('IndexController', ['$scope', 'menuFactory', 'corporateFactory', function ($scope, menuFactory, corporateFactory) 
    {
        $scope.showDish = false;
        $scope.message="Loading ...";
        $scope.dish = menuFactory.getDishes().get({id: 0}).$promise.then(
            function(response)
            {
                $scope.dish = response;
                $scope.showDish = true;
            },
            
            function(response) 
            {
                $scope.message = "Error: "+response.status + " " + response.statusText;
            }
        );
        
        $scope.featuredPromotion = menuFactory.getPromotions().get({id: 0}).$promise.then(
            function (response) 
            {
                $scope.featuredPromotion = response;
                $scope.showPromotion = true;
            },
            
            function (response) 
            {
                $scope.message = "Error: " + response.status + " " + response.statusText;
            }
        );
        
        $scope.executiveChef = corporateFactory.getLeaders().get({id: 3}).$promise.then(
            function (response) 
            {
                $scope.executiveChef = response;
                $scope.showLeader = true;
            },
            
            function (response) 
            {
                $scope.message = "Error: " + response.status + " " + response.statusText;
            }
        );
    }])

    .controller('AboutController', ['$scope', 'corporateFactory', function ($scope, corporateFactory) 
    {
        $scope.showLeaders = false;

        $scope.leaders = corporateFactory.getLeaders().query(
            function (response) 
            {
                $scope.leaders = response;
                $scope.showLeaders = true;
            },
            
            function (response) 
            {
                $scope.message = "Error: " + response.status + " " + response.statusText;
            }
        );
    }])

    .controller('FeedbackController', ['$scope', 'feedbackFactory', function ($scope, feedbackFactory) 
    {
        $scope.sendFeedback = function () 
        {
            if ($scope.feedback.agree && ($scope.feedback.mychannel === "")) 
            {
                $scope.invalidChannelSelection = true;
            }
            else 
            {
                $scope.invalidChannelSelection = false;
                feedbackFactory.getFeedback().save($scope.feedback);
                $scope.feedbackForm.$setPristine();
                $scope.feedback = 
                {
                    mychannel: "", 
                    firstName: "", 
                    lastName: "", 
                    agree: false, 
                    email: ""
                };
            }
        };
    }])
;